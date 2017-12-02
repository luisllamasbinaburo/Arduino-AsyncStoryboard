/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "StoryBoard.h"

StoryBoard storyBoard(10);
StoryBoard StoryBoardAux(5);

void debug(String text)
{
	Serial.print(millis());
	Serial.print('\t');
	Serial.println(text);
}

void flash(const int num, const int delayTime)
{
	for (int index = 0; index < num; index++)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(delayTime);
		digitalWrite(LED_BUILTIN, LOW);
		delay(delayTime);
	}
}

//void TurnOn()
//{
//	storyBoard.AddTask(500, []() {digitalWrite(LED_BUILTIN, HIGH);}, TurnOff);
//}
//void TurnOff()
//{
//	storyBoard.AddTask(500, []() {digitalWrite(LED_BUILTIN, LOW);}, TurnOn);
//}
//
//void loopTask()
//{
//	storyBoardAux.AddTask(1500, []() {debug("Debug 1");}, nullptr);
//	storyBoardAux.AddTask(1000, []() {debug("Debug 2");}, nullptr);
//	storyBoardAux.AddTask(2000, []() {debug("Debug 3");}, loopTask);
//}
//
//void nextTask()
//{
//	storyBoard.AddTask(200, []() {debug("Debug9");}, nullptr);
//	storyBoard.AddTask(300, []() {debug("Debug10");}, nullptr);
//	storyBoard.AddTask(400, []() {debug("Debug11");}, nullptr);
//	storyBoard.AddTask(200, []() {debug("Debug12");}, nullptr);
//}

void setup() 
{
	Serial.begin(115200);

	//loopTask();
	//TurnOn();

	/*storyBoard.AddTask(500, []() {debug("Debug1");}, nullptr);
	storyBoard.AddTask(200, []() {debug("Debug2");}, nullptr);
	storyBoard.AddTask(300, []() {debug("Debug3");}, nextTask);
	storyBoard.AddTask(100, []() {debug("Debug4");}, nullptr);
	storyBoard.AddTask(200, []() {debug("Debug5");}, nullptr);
	storyBoard.AddTask(300, []() {debug("Debug6");}, nullptr);
	storyBoard.AddTask(100, []() {debug("Debug7");}, nullptr);
	storyBoard.AddTask(300, []() {debug("Debug8");}, nextTask);

	storyBoardAux.AddTask(300, []() {debug("Debug21");}, nullptr);
	storyBoardAux.AddTask(300, []() {debug("Debug22");}, nullptr);*/

	//storyBoard.AddRepetitiveTask(1000, []() {debug("Repeat 1");}, 5, nullptr);
	//storyBoard.AddRepetitiveTask(350, []() {debug("Repeat 2");}, 5, nullptr);

//	storyBoard.AddAlternant(500, []() {debug("Alternate 1");}, []() {debug("Alternate 2");}, 5, nullptr);
	storyBoard.AddSingle(500, []() {debug("Debug1");});
	storyBoard.AddDelay(1500);
	storyBoard.AddRepetitive(500, 
		[]() {debug("Debug2");}, 3, 
		[]() {storyBoard.AddAlternant(500, []() {debug("Alternant1");}, []() {debug("Alternant2");}, 2);});

	
	//storyBoard.AddDelay(2000, []() {debug("Delay");});
	//storyBoard.AddRepetitive(200, []() {debug("Repeat");}, 0, nullptr);

	//storyBoardAux.AddTask(100, []() {debug("Debug7");}, nullptr);
	//storyBoardAux.AddRepetitiveTask(800, []() {debug("Repeat");}, 0, nullptr);
}


	//storyBoard.AddTask(3000, []() {flash(1, 100);}, nullptr);
	//storyBoard.AddTask(1000, []() {flash(2, 100);}, nullptr);
	//storyBoard.AddTask(2000, []() {flash(3, 100);}, nullptr);

void loop()
{
	Serial.println("Main Loop");
	while (1)
	{
		storyBoard.Update();
		//storyBoardAux.Update();
	}
}
