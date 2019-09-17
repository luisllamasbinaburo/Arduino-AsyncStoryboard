/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _StoryBoardLib_h
#define _StoryBoardLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

typedef  void(*Action)();

struct Task
{
	unsigned long time;
	unsigned long trigger;
	unsigned int repetitions;
	Action action;
	Action alternateAction;
	Action next;
	Action callback;
};

class StoryBoard
{
public:
	StoryBoard(const size_t capacity);

	size_t Capacity() const;
	size_t Count() const;

	void AddDelay(int time);
	void AddDelay(int time, Action callback);
	void AddSingle(int time, Action action);
	void AddSingle(int time, Action action, Action callback);

	void AddRepetitive(int time, Action action, unsigned int repetitions);
	void AddRepetitive(int time, Action action, unsigned int repetitions, Action callback);
	void AddContinuous(int time, Action action);
	void AddContinuous(int time, Action action, Action callback);

	void AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions);
	void AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions, Action callback);
	void AddAlternantContinuous(int time, Action action, Action alternateAction);
	void AddAlternantContinuous(int time, Action action, Action alternateAction, Action callback);

	void Update();

	bool IsFull() const;
	bool IsEmpty() const;

private:
	Task* _items;
	Task* _itemsEnd;

	Task* _firstAccessor;
	Task* _lastAccessor;
	size_t _capacity;
	size_t _count;

	unsigned long _currentMillis;
	unsigned long _lastMillis;

	void addTask(int time, Action action, Action alternateAction, unsigned int repetitions, Action callback);
	void removeTask();
	void processTask(Task* task);

	void incAccessor(Task** accessor);
	void decAccessor(Task** accessor);
	void incCounter();
	void decCounter();
};

#endif
