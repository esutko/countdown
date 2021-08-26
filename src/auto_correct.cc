#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iterator>

#include <iostream>
#include <cctype>

#include "events_data.h"
#include "slice.h"

#include "auto_correct.h"

using namespace std;

void add_word(set<string> &words, const string &w, bool signifcant) {
	const static unordered_set<string> minor {"the", "and", "of", "in", "for", "a", "an"};
	if (!w.empty() && (!signifcant || !minor.count(w)))
		words.insert(w);
}

set<string> get_words(const string &s, bool signifcant) {
	set<string> words;
	string partial_word;

	for (char c : s) {
		if (isspace(c)) {
			add_word(words, partial_word, signifcant);
			partial_word = "";	
		} else {
			partial_word += tolower(c);
		}
	}
	add_word(words, partial_word, signifcant);

	return words;
}

void find_sums(const string &elem, const set<string> &search, set<string> &both, double &any_size) {
	for (auto i = search.begin(); i != search.end(); ++i) {
		if (i->size() >= elem.size())
			continue;
		for (auto j = i; j != search.end(); ++j) {
			if (i->size() + j->size() != elem.size())
				continue;
			if (elem == *i + *j || elem == *j + *i) {
				--any_size;
				both.insert(*i);
				both.insert(*j);
			}
		}
	}
}

double similar (const string &str1, const string &str2) {
	set<string> words1 = get_words(str1, true);
	set<string> words2 = get_words(str2, true);

	set<string> both;
	set_intersection(
		words1.begin(), words1.end(),
		words2.begin(), words2.end(),
		inserter(both, both.end())
	);
	double any_size = words1.size() + words2.size() - both.size();


	// Find pairs that add up to another element ie. antman, ant, man
	for (string elem : words1)
		find_sums(elem, words2, both, any_size);
	for (string elem : words2)
		find_sums(elem, words1, both, any_size);

	// if one contians a digit both must contain the digit or return a score of 0;
	for (string w : words1)
		if (all_of(w.begin(), w.end(), [](char c){return isdigit(c);}) && !both.count(w))
			return 0;
	for (string w : words2)
		if (all_of(w.begin(), w.end(), [](char c){return isdigit(c);}) && !both.count(w))
			return 0;

	return both.size()/any_size;
}

string auto_correct(const Slice<Event> &events, const string &name) {
	vector<double> scores;
	transform(
		events.begin(), events.end(),
		back_inserter(scores),
		[name](Event e){return similar(name, e.name);}
	);
	auto max = max_element(scores.begin(), scores.end());
	
	auto iter = events.begin();
	advance(iter, max - scores.begin());
	string remplacement = (*iter).name;
	
	if (*max < .5 || remplacement == name)
		return name;

	cout << "did you mean \"" << remplacement << "\"? [y/n] ";
	string confirm;
	cin >> confirm;

	if (confirm[0] == 'y') {
		return remplacement;
	} else {
		return name;
	}
}