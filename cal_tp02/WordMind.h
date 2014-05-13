//
//  WordMind.h
//  cal_tp02
//
//  Created by Eduardo Almeida on 13/05/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#ifndef __cal_tp02__WordMind__
#define __cal_tp02__WordMind__

#include <iostream>

#include "Dictionary.h"

enum class WordMindState : unsigned int { NOPE = 0, WRONG_PLACE = 1, CORRECT = 2 };

class WordMind {
    
    WordMind();
    
    void _parseGuessState();
    
    std::vector<std::string> _possibleWords;
    
    std::vector<WordMindState> _guessState;
    
    std::string _currentWord;
    
public:
    
    WordMind(Dictionary *dict, int length);
    
    void guess();
    
    void setState(std::vector<WordMindState> guessState);
    
    std::string getCurrentWord();
    
    double getCertainity();
    
};

#endif /* defined(__cal_tp02__WordMind__) */
