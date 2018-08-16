
// File:        main.cpp
// Author:      cheeren
// Date:        2018-03-31
// Description: Partial test of PA4 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{
	PNG test1;
	test1.readFromFile("images/simpleLine.png");
	pair<int,int> test1Start(5,10);
    pair<int,int> test1EasyEnd(15,15);
	pair<int,int> test1FullEnd(55,38);
	path t1Short(test1,test1Start, test1EasyEnd);
	path t1Long(test1,test1Start, test1FullEnd);
    cout << t1Short.length() << endl;
	cout << t1Long.length() << endl;
	PNG shortLine = t1Short.render();
	PNG fullLine = t1Long.render();
	shortLine.writeToFile("images/output-test1-short.png");
	fullLine.writeToFile("images/output-test1-full.png");

	PNG test2;
	test1.readFromFile("images/pulse.png");
	pair<int,int> test2Start(127,131);
    pair<int,int> test2End(139, 57);
	path test2p(test1,test2Start, test2End);
    cout << test2p.length() << endl;
	PNG test2img = test2p.render();
	test2img.writeToFile("images/output-pulsePath.png");	
	

	PNG origIm1;
	origIm1.readFromFile("images/snake.png");
	pair<int,int> start1(2,2);
    pair<int,int> end1(637,477);
	path snake(origIm1,start1,end1);
    cout << snake.length() << endl;
	PNG out1 = snake.render();
	out1.writeToFile("images/output-snakePath.png");

	PNG origIm2;
	origIm2.readFromFile("images/maze.png");
	pair<int,int> start2(3,10);
    pair<int,int> end2(637,477);
	path maze(origIm2,start2,end2);
    cout << maze.length() << endl;
	PNG out2 = maze.render();
	out2.writeToFile("images/output-mazePath.png");

	PNG midMaze;
	test1.readFromFile("images/middleMaze.png");
	pair<int,int> maze2Start(221,183);
    pair<int,int> maze2EasyEnd(243,29);
	pair<int,int> maze2FullEnd(406,267);
	path maze2Short(test1,maze2Start, maze2EasyEnd);
	path maze2Long(test1,maze2Start, maze2FullEnd);
    cout << maze2Short.length() << endl;
	cout << maze2Long.length() << endl;
	PNG m2Short = maze2Short.render();
	PNG m2Long = maze2Long.render();
	m2Short.writeToFile("images/output-maze2-short.png");
	m2Long.writeToFile("images/output-maze2-long.png");
	
	PNG origIm3;
	origIm3.readFromFile("images/sunshine.png");
	pair<int,int> start3(320,420);
    pair<int,int> end3(100,100);
	path sunshine(origIm3,start3,end3);
    cout << sunshine.length() << endl;
	PNG out3 = sunshine.render();
	out3.writeToFile("images/output-sunshinePath.png");

  return 0;
}
