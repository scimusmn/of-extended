#ifndef _THREADED_OBJECT
#define _THREADED_OBJECT

#include "ofMain.h"
#include "ofxThread.h"




class ofSysCall : public ofxThread{

	public:

	bool	newCommand;
	string	command;

	    int count;  // threaded fucntions that share data need to use lock (mutex)
	                // and unlock in order to write to that data
	                // otherwise it's possible to get crashes.
	                //
	                // also no opengl specific stuff will work in a thread...
	                // threads can't create textures, or draw stuff on the screen
	                // since opengl is single thread safe

		//--------------------------
		threadedObject(){
			count = 0;
		}

		void start(){
            startThread(true, false);   // blocking, verbose
        }

        void stop(){
            stopThread();
        }

		//--------------------------
		void threadedFunction(){

			while( isThreadRunning() != 0 ){
				if( lock() ){
					if(newCommand){
						system(command.c_str());
						newCommand=false;
					}
					unlock();
					stop();
				}
			}
		}

		//--------------------------
		void runSystemCall(string cmd){
			
			if( lock() ){
				command=cmd;
				newCommand=true;
				start();
				unlock();
			}
			
		}
	
	bool callIsRunning(){

		return (isThreadRunning() !=0);
	}



};

#endif
