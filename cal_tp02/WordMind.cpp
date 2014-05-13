//
//  WordMind.cpp
//  cal_tp02
//
//  Created by Eduardo Almeida on 13/05/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include <map>

#include "WordMind.h"

typedef struct charstat {
    char c;
    bool s;
} charstat;

WordMind::WordMind(Dictionary *dict, int length) {
    _possibleWords = dict -> getWords(length);
}

void WordMind::_parseGuessState() {
    std::vector<char> mustNotContain;
    
    std::map<int, char> mustContainAt;
    std::map<int, charstat> mustContainButNotAt;
    
    for (auto i = 0; i < _currentWord.length(); i++) {
        switch (_guessState[i]) {
            case WordMindState::NOPE:
                
                mustNotContain.push_back(_currentWord[i]);
                
                break;
                
            case WordMindState::WRONG_PLACE: {
                
                charstat cs = { .c = _currentWord[i], .s = false };
                
                mustContainButNotAt.insert(std::pair<int, charstat>(i, cs));
                
                break;
                
            }
                
            case WordMindState::CORRECT:
                
                mustContainAt.insert(std::pair<int, char>(i, _currentWord[i]));
                
                break;
                
            default:
                
                throw "Are you serious?!";
                
                break;
        }
    }
    
    for (auto i = 0; i < _possibleWords.size(); i++) {
        auto word = _possibleWords[i];
        
        bool removeWord = false;
        
        unsigned int mcbnaOccurences = 0;    //  Must contain but not at occurence counter...
        
        for (auto i = 0; i < word.length(); i++) {
            auto c = word[i];
            
            //
            //  mustNotContain check
            //
            
            for (auto mnc : mustNotContain)
                if (c == mnc) {
                    removeWord = true;
                    
                    break;
                }
            
            if (removeWord)
                break;
            
            //
            //  mustContainAt check
            //
            
            if (mustContainAt.find(i) != mustContainAt.end())
                if (mustContainAt[i] != c)
                    removeWord = true;
            
            if (removeWord)
                break;
            
            //
            //  mustContainButNotAt check
            //
            
            typedef std::map<int, charstat>::iterator it_type;
            
            for (it_type it = mustContainButNotAt.begin(); it != mustContainButNotAt.end(); it++) {
                auto cs = it->second;
                
                if (!cs.s) {
                    if (cs.c == c) {
                        it->second.s = true;
                        
                        mcbnaOccurences++;
                    }
                    
                    break;
                }
            }
            
            if (mustContainButNotAt.find(i) != mustContainButNotAt.end())
                if (mustContainButNotAt[i].c == c)
                    removeWord = true;
            
            if (removeWord)
                break;
        }
        
        if (removeWord || mcbnaOccurences != mustContainButNotAt.size()) {
            _possibleWords.erase(_possibleWords.begin() + i);
            
            i--;
        }
    }
}

void WordMind::guess() {
    if (_currentWord.length())
        _parseGuessState();
    
    _currentWord = _possibleWords[0];
    
    _possibleWords.erase(_possibleWords.begin());
}

void WordMind::setState(std::vector<WordMindState> guessState) {
    _guessState = guessState;
}

std::string WordMind::getCurrentWord() {
    return _currentWord;
}

double WordMind::getCertainity() {
    return 1.0f / _possibleWords.size();
}