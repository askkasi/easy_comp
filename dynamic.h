/**
 * @file dynamic.h
 * @author Deniz Deli <br>
 * Sound Engineer, Berlin University of the Arts<br>
 * <br>
 * A dynamic-processor object for pure data <br>
 * <br>
 * @brief A Pure Data dynamic-processor object for adjusting the dynamic of audio files<br>
 * <br>
 * dynamic~ allows for adjusting the dynamic<br>
 * of any incoming mono audio signal. <br>
 * <br>
 */

#ifndef dynamic_h
#define dynamic_h

#include <stdio.h>
#include <stdlib.h>


typedef float INPUTVECTOR;
typedef float OUTPUTVECTOR;

/**
 * @struct dynamic
 * @brief A structure for a dynamic object <br>
 * @var stp::level The parameter value for adjusting the <br>
 * level of the incoming signal
 */

typedef struct dynamic
{
	float threshold; /**< parameter for adjusting the threshold of the compressor */
	float ratio; /**< parameter for adjusting the ratio of the compression */
	float attack; /**< parameter for adjusting the attack time of the compressor */
	float release; /**< parameter for adjusting the release time of the compressor */
	float makeUpGain; /**< parameter for adjusting the level of the signal after compression*/
    float clippingLevel; /**< parameter for clipping the level of the outgoing signal */
} dynamic;

/**
 * @related dynamic
 * @brief Creates a new dynamic object<br>
 * The function creates a new dynamic object <br>
 * @return a pointer to the newly created dynamic object <br>
 */

dynamic *dynamic_new();

/**
 * @related dynamic
 * @brief Frees a dynamic object<br>
 * @param x My dynamic object to delete.<br>
 * The function frees the allocated memory<br>
 * of a dynamic object
 */

void dynamic_free(dynamic *x);

/**
 * @related dynamic
 * @brief Sets the threshold parameter <br>
 * @param x My dynamic object <br>
 * @param threshold The gain value <br>
 * The function sets the threshold parameter of <br>
 * the gain class
 */

void dynamic_setThreshold(dynamic *x, float threshold);

/**
 * @related dynamic
 * @brief Sets the ratio parameter <br>
 * @param x My dynamic object <br>
 * @param ratio The gain value <br>
 * The function sets the ratio parameter of <br>
 * the gain class
 */

void dynamic_setRatio(dynamic *x, float ratio);

/**
 * @related dynamic
 * @brief Sets the attack parameter <br>
 * @param x My dynamic object <br>
 * @param attack The gain value <br>
 * The function sets the attack parameter of <br>
 * the gain class
 */

void dynamic_setAttack(dynamic *x, float attack);

/**
 * @related dynamic
 * @brief Sets the release parameter <br>
 * @param x My dynamic object <br>
 * @param release The gain value <br>
 * The function sets the release parameter of <br>
 * the gain class
 */

void dynamic_setRelease(dynamic *x, float release);

/**
 * @related dynamic
 * @brief Sets the gain parameter <br>
 * @param x My dynamic object <br>
 * @param makeUpGain The gain value <br>
 * The function sets the makeUpGain parameter of <br>
 * the gain class
 */

void dynamic_setMakeUpGain(dynamic *x, float makeUpGain);

/**
 * @related dynamic
 * @brief Sets the clippingLevel parameter <br>
 * @param x My dynamic object <br>
 * @param clippingLevel The clippingLevel value <br>
 * The function sets the clippingLevel parameter of <br>
 * the gain class
 */

void dynamic_setClippingLevel(dynamic *x, float clippingLevel);

/**
 * @related dynamic
 * @brief Performs the level makeup in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function dynamic_makeUp multiplies the input signal <br>
 * with the parameter gain. <br>
 */

void dynamic_makeUp(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize);

/**
 * @related dynamic
 * @brief Performs the clipping in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function dynamic_clip sets every value of the input signal <br>
 * thats either greater then the parameter clippingLevel or smaller then the <br>
 * parameter -clippingLevel to either clippingLevel or -clippingLevel. <br>
 */

void dynamic_clip(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize);

/**
 * @related dynamic
 * @brief Performs the level adjustment in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function dynamic_perform performs the gain adjustment of <br>
 * the incoming signal and copies the result to the output vector <br>
 */

void dynamic_perform(dynamic *x, INPUTVECTOR *in, OUTPUTVECTOR *out, int vectorSize);

#endif /* dynamic_h */
