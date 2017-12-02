/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "StoryBoardLib.h"

StoryBoard::StoryBoard(const size_t capacity)
{
	_items = new Task[capacity];
	_itemsEnd = _items + capacity - 1;

	_firstAccessor = _items;
	_lastAccessor = _items;
	_capacity = capacity;
	_count = 0;
	_lastMillis = 0;
}

size_t StoryBoard::Capacity() const
{
	return _capacity;
}

size_t StoryBoard::Count() const
{
	return _count;
}

void StoryBoard::AddDelay(int time)
{
	addTask(time, nullptr, nullptr, 1, nullptr);
}

void StoryBoard::AddDelay(int time, Action callback)
{
	addTask(time, nullptr, nullptr, 1, callback);
}

void StoryBoard::AddSingle(int time, Action action)
{
	addTask(time, action, nullptr, 1, nullptr);
}

void StoryBoard::AddSingle(int time, Action action, Action callback)
{
	addTask(time, action, nullptr, 1, callback);
}

void StoryBoard::AddRepetitive(int time, Action action, unsigned int repetitions)
{
	addTask(time, action, nullptr, repetitions, nullptr);
}

void StoryBoard::AddRepetitive(int time, Action action, unsigned int repetitions, Action callback)
{
	addTask(time, action, nullptr, repetitions, callback);
}

void StoryBoard::AddContinuous(int time, Action action)
{
	addTask(time, action, nullptr, 0, nullptr);
}

void StoryBoard::AddContinuous(int time, Action action, Action callback)
{
	addTask(time, action, nullptr, 0, callback);
}

void StoryBoard::AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions)
{
	addTask(time, action, alternateAction, repetitions, nullptr);
}

void StoryBoard::AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions, Action callback)
{
	addTask(time, action, alternateAction, repetitions, callback);
}

void StoryBoard::AddAlternantContinuous(int time, Action action, Action alternateAction)
{
	addTask(time, action, alternateAction, 0, nullptr);
}

void StoryBoard::AddAlternantContinuous(int time, Action action, Action alternateAction, Action callback)
{
	addTask(time, action, alternateAction, 0, callback);
}

void StoryBoard::Update()
{
	if (_count == 0) return;

	_currentMillis = millis();
	
	if (IsEmpty()) return;

	if ( static_cast<unsigned long>(_currentMillis) - _firstAccessor->trigger <= 0)
		processTask(_firstAccessor);
}

void StoryBoard::addTask(int time, Action action, Action alternateAction, unsigned int repetitions, Action callback)
{
	if (IsFull()) return;

	if (_count > 0)
		incAccessor(&_lastAccessor);

	incCounter();

	_lastAccessor->action = action;
	_lastAccessor->alternateAction = alternateAction;
	_lastAccessor->repetitions = repetitions;
	_lastAccessor->callback = callback;
	_lastAccessor->time = time;

	_lastMillis = time + _lastMillis;
	_lastAccessor->trigger = _lastMillis;
}

void StoryBoard::removeTask()
{
	if(_count > 1)
		incAccessor(&_firstAccessor);

	decCounter();
}

void StoryBoard::processTask(Task* task)
{
	if (task->action != nullptr)  task->action();

	removeTask();
	
    if (task->repetitions == 0)
		if(task->alternateAction == nullptr)
 			AddRepetitive(task->time, task->action, 0, task->callback);
		else
			AddAlternant(task->time, task->alternateAction, task->action, 0, task->callback);

	if (task->repetitions > 1)
		if (task->alternateAction == nullptr)
			AddRepetitive(task->time, task->action, task->repetitions - 1, task->callback);
		else
			AddAlternant(task->time, task->alternateAction, task->action, task->repetitions - 1, task->callback);

	if(task->repetitions <= 1 && task->callback != nullptr) task->callback();
		
}

bool StoryBoard::IsFull() const
{
	return _count >= _capacity;
}

bool StoryBoard::IsEmpty() const
{
	return _count == 0;
}

inline void StoryBoard::incAccessor(Task** accessor)
{
	++(*accessor);
	if ((*accessor) > _itemsEnd) 
		(*accessor) = _items;
}

inline void StoryBoard::decAccessor(Task** accessor)
{
	--*accessor;
	if (*accessor < _items) 
		*accessor = _itemsEnd;
}

void StoryBoard::incCounter()
{

	if (_count < _capacity)
		++_count;
}

void StoryBoard::decCounter()
{
	if (_count > 0)
		--_count;
}