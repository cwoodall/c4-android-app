#include <jni.h>
#include "C4Player.h"

// Declare a static global (to the C++) C4Game.
static C4Game c4_game;
static C4HumanPlayer p1('r');
static C4HumanPlayer p2_human('b');
static C4AIPlayer p2_ai('b');

extern "C" {
    // Check Function calls
    JNIEXPORT void JNICALL
    Java_team7_c7_MainActivity_gameReset(JNIEnv *env, jobject obj) {
	c4_game.reset();
    }

    // Check Function calls
    JNIEXPORT void JNICALL
    Java_team7_c7_MainActivity_setupGame(JNIEnv *env, jobject obj, jint ai) {
	if (ai)
	    c4_game.init(&p1, &p2_ai);
	else
	    c4_game.init(&p1, &p2_human);
    }

    // Check Function calls
    JNIEXPORT jint JNICALL
    Java_team7_c7_MainActivity_getGameState(JNIEnv *env, jobject obj) {
	return (jint) c4_game.getGameState();
    }

    // Check Function calls
    JNIEXPORT jint JNICALL
    Java_team7_c7_MainActivity_isCurrentAI(JNIEnv *env, jobject obj) {
	return (jint) c4_game.isCurrentAI();
    }

    // Check Function calls
    JNIEXPORT jint JNICALL
    Java_team7_c7_MainActivity_makeGameMove (JNIEnv *env, jobject obj, jint move) {
    	if (c4_game.step((int) move) == -1)
    		return (jint) -1;
    	else
    		return (jint) c4_game.getLastMove();
    }

    JNIEXPORT jint JNICALL
    Java_team7_c7_MainActivity_getCurrentPlayer(JNIEnv *env, jobject obj) {
    	return (jint) c4_game.getCurrentPlayer();
    }

    JNIEXPORT jint JNICALL
    Java_team7_c7_MainActivity_getLastMove(JNIEnv *env, jobject obj) {
    	return (jint) c4_game.getLastMove();
    }
}
