/**
 * @file easy_comp~.c
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

#include "m_pd.h"
#include "dynamic.h"
//#include "dynamic_testing.h"

static t_class *easy_comp_tilde_class;

/**
 * @struct dynamic_tilde
 * @brief The Pure Data struct of the dynamic~ object. <br>
 * @var dynamic_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var dynamic_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var dynamic_tilde::gain The gain object for the actual signal processing <br>
 * @var dynamic_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct easy_comp_tilde
{
    t_object  x_obj;
    t_sample f;
    dynamic *dynamic;
    t_outlet*x_out;
} easy_comp_tilde;

/**
 * @related dynamic_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the dynamic_perform method. <br>
 * @return A pointer to the signal chain right behind the dynamic_tilde object. <br>
 */

t_int *easy_comp_tilde_perform(t_int *w)
{
    easy_comp_tilde *x = (easy_comp_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    dynamic_perform(x->dynamic, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related dynamic_tilde
 * @brief Adds dynamic_tilde_perform to the signal chain. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void easy_comp_tilde_dsp(easy_comp_tilde *x, t_signal **sp)
{
    dsp_add(easy_comp_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related dynamic_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void easy_comp_tilde_free(easy_comp_tilde *x)
{
    outlet_free(x->x_out);
    dynamic_free(x->dynamic);
}

/**
 * @related dynamic_tilde
 * @brief Creates a new dynamic_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *easy_comp_tilde_new(t_floatarg threshold, t_floatarg ratio, t_floatarg attack, t_floatarg release, t_floatarg makeUpGain, t_floatarg clippingLevel)
{
    easy_comp_tilde *x = (easy_comp_tilde *)pd_new(easy_comp_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->dynamic = dynamic_new();
    x->dynamic->threshold = threshold;
    x->dynamic->ratio = ratio;
    x->dynamic->attack = attack;
    x->dynamic->release = release;
    x->dynamic->makeUpGain = makeUpGain;
    x->dynamic->clippingLevel = clippingLevel;

    return (void *)x;
}


/**
 * @related dynamic_tilde
 * @brief Sets the threshold parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param threshold Sets the threshold parameter <br>
 */

void easy_comp_tilde_setThreshold(easy_comp_tilde *x, float threshold)
{
    dynamic_setTreshold(x->dynamic, threshold);
}

/**
 * @related dynamic_tilde
 * @brief Sets the ratio parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param ratio Sets the ratio parameter <br>
 */

void easy_comp_tilde_setRatio(easy_comp_tilde *x, float ratio)
{
    dynamic_setRatio(x->dynamic, ratio);
}

/**
 * @related dynamic_tilde
 * @brief Sets the attack parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param attack Sets the attack parameter <br>
 */

void easy_comp_tilde_setAttack(easy_comp_tilde *x, float attack)
{
    dynamic_setAttack(x->dynamic, attack);
}

/**
 * @related dynamic_tilde
 * @brief Sets the release parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param release Sets the release parameter <br>
 */

void easy_comp_tilde_setRelease(easy_comp_tilde *x, float release)
{
    dynamic_setRelease(x->dynamic, release);
}

/**
 * @related dynamic_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param level Sets the level parameter <br>
 */

void easy_comp_tilde_setMakeUpGain(easy_comp_tilde *x, float makeUpGain)
{
    dynamic_setMakeUpGain(x->dynamic, makeUpGain);
}

/**
 * @related dynamic_tilde
 * @brief Sets the clipping level parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param makeUpLevel Sets the makeUpLevel parameter <br>
 */

void easy_comp_tilde_setClippingLevel(easy_comp_tilde *x, float clippingLevel)
{
    dynamic_setClippingLevel(x->dynamic, clippingLevel);
}

/**
 * @related dynamic_tilde
 * @brief Sets the clipping level parameter. <br>
 * @param x A pointer the dynamic_tilde object <br>
 * @param makeUpLevel Sets the makeUpLevel parameter <br>
 */

/*void easy_comp_tilde_integrationTest(easy_comp_tilde *x)
{
    dynamicTest *test = dynamicTest_new(x->dynamic, 32, 64);
    dynamicTest_integration(test);
    dynamicTest_free(test);
}*/

/**
 * @related dynamic_tilde
 * @brief Setup of dynamic_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void easy_comp_tilde_setup(void)
{
      easy_comp_tilde_class = class_new(gensym("easy_comp~"), (t_newmethod)easy_comp_tilde_new, (t_method)easy_comp_tilde_free,
                                            sizeof(easy_comp_tilde), CLASS_DEFAULT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT/*0*/);

      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_dsp, gensym("dsp"), 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setThreshold, gensym("threshold"), A_DEFFLOAT, 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setRatio, gensym("ratio"), A_DEFFLOAT, 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setAttack, gensym("attack"), A_DEFFLOAT, 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setRelease, gensym("release"), A_DEFFLOAT, 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setMakeUpGain, gensym("makeupgain"), A_DEFFLOAT, 0);
      class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_setClippingLevel, gensym("clippinglevel"), A_DEFFLOAT, 0);
      //class_addmethod(easy_comp_tilde_class, (t_method)easy_comp_tilde_integrationTest, gensym("integrationtest"), 0);
      CLASS_MAINSIGNALIN(easy_comp_tilde_class, easy_comp_tilde, f);
}
