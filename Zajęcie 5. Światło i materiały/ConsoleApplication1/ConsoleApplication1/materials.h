/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/

#ifndef __MATERIALS__H__
#define __MATERIALS__H__

#include <GL/gl.h>

// mosiπdz

const GLfloat BrassAmbient [4] =
    {
        0.329412, 0.223529, 0.027451, 1.000000
    };

const GLfloat BrassDiffuse [4] =
    {
        0.780392, 0.568627, 0.113725, 1.000000
    };

const GLfloat BrassSpecular [4] =
    {
        0.992157, 0.941176, 0.807843, 1.000000
    };

const GLfloat BrassShininess = 27.8974;

// brπz

const GLfloat BronzeAmbient [4] =
    {
        0.212500, 0.127500, 0.054000, 1.000000
    };

const GLfloat BronzeDiffuse [4] =
    {
        0.714000, 0.428400, 0.181440, 1.000000
    };

const GLfloat BronzeSpecular [4] =
    {
        0.393548, 0.271906, 0.166721, 1.000000
    };

const GLfloat BronzeShininess = 25.6;

// polerowany brπz

const GLfloat PolishedBronzeAmbient [4] =
    {
        0.250000, 0.148000, 0.064750, 1.000000
    };

const GLfloat PolishedBronzeDiffuse [4] =
    {
        0.400000, 0.236800, 0.103600, 1.000000
    };

const GLfloat PolishedBronzeSpecular [4] =
    {
        0.774597, 0.458561, 0.200621, 1.000000
    };

const GLfloat PolishedBronzeShininess = 76.8;

// chrom

const GLfloat ChromeAmbient [4] =
    {
        0.250000, 0.250000, 0.250000, 1.000000
    };

const GLfloat ChromeDiffuse [4] =
    {
        0.400000, 0.400000, 0.400000, 1.000000
    };

const GLfloat ChromeSpecular [4] =
    {
        0.774597, 0.774597, 0.774597, 1.000000
    };

const GLfloat ChromeShininess = 76.8;

// miedü

const GLfloat CopperAmbient [4] =
    {
        0.191250, 0.073500, 0.022500, 1.000000
    };

const GLfloat CopperDiffuse [4] =
    {
        0.703800, 0.270480, 0.082800, 1.000000
    };

const GLfloat CopperSpecular [4] =
    {
        0.256777, 0.137622, 0.086014, 1.000000
    };

const GLfloat CopperShininess = 12.8;

// polerowana miedü

const GLfloat PolishedCopperAmbient [4] =
    {
        0.229500, 0.088250, 0.027500, 1.000000
    };

const GLfloat PolishedCopperDiffuse [4] =
    {
        0.550800, 0.211800, 0.066000, 1.000000
    };

const GLfloat PolishedCopperSpecular [4] =
    {
        0.580594, 0.223257, 0.069570, 1.000000
    };

const GLfloat PolishedCopperShininess = 51.2;

// z≥oto

const GLfloat GoldAmbient [4] =
    {
        0.247250, 0.199500, 0.074500, 1.000000
    };

const GLfloat GoldDiffuse [4] =
    {
        0.751640, 0.606480, 0.226480, 1.000000
    };

const GLfloat GoldSpecular [4] =
    {
        0.628281, 0.555802, 0.366065, 1.000000
    };

const GLfloat GoldShininess = 52.2;

// polerowane z≥oto

const GLfloat PolishedGoldAmbient [4] =
    {
        0.247250, 0.224500, 0.064500, 1.000000
    };

const GLfloat PolishedGoldDiffuse [4] =
    {
        0.346150, 0.314300, 0.090300, 1.000000
    };

const GLfloat PolishedGoldSpecular [4] =
    {
        0.797357, 0.723991, 0.208006, 1.000000
    };

const GLfloat PolishedGoldShininess = 83.2;

// cyna z o≥owiem (grafit)

const GLfloat PewterAmbient [4] =
    {
        0.105882, 0.058824, 0.113725, 1.000000
    };

const GLfloat PewterDiffuse [4] =
    {
        0.427451, 0.470588, 0.541176, 1.000000
    };

const GLfloat PewterSpecular [4] =
    {
        0.333333, 0.333333, 0.521569, 1.000000
    };

const GLfloat PewterShininess = 9.84615;

// srebro

const GLfloat SilverAmbient [4] =
    {
        0.192250, 0.192250, 0.192250, 1.000000
    };

const GLfloat SilverDiffuse [4] =
    {
        0.507540, 0.507540, 0.507540, 1.000000
    };

const GLfloat SilverSpecular [4] =
    {
        0.508273, 0.508273, 0.508273, 1.000000
    };

const GLfloat SilverShininess = 51.2;

// polerowane srebro

const GLfloat PolishedSilverAmbient [4] =
    {
        0.231250, 0.231250, 0.231250, 1.000000
    };

const GLfloat PolishedSilverDiffuse [4] =
    {
        0.277500, 0.277500, 0.277500, 1.000000
    };

const GLfloat PolishedSilverSpecular [4] =
    {
        0.773911, 0.773911, 0.773911, 1.000000
    };

const GLfloat PolishedSilverShininess = 89.6;

// szmaragd

const GLfloat EmeraldAmbient [4] =
    {
        0.021500, 0.174500, 0.021500, 0.550000
    };

const GLfloat EmeraldDiffuse [4] =
    {
        0.075680, 0.614240, 0.075680, 0.550000
    };

const GLfloat EmeraldSpecular [4] =
    {
        0.633000, 0.727811, 0.633000, 0.550000
    };

const GLfloat EmeraldShininess = 76.8;

// jadeit

const GLfloat JadeAmbient [4] =
    {
        0.135000, 0.222500, 0.157500, 0.950000
    };

const GLfloat JadeDiffuse [4] =
    {
        0.540000, 0.890000, 0.630000, 0.950000
    };

const GLfloat JadeSpecular [4] =
    {
        0.316228, 0.316228, 0.316228, 0.950000
    };

const GLfloat JadeShininess = 12.8;

// obsydian (szk≥o wulkaniczne)

const GLfloat ObsidianAmbient [4] =
    {
        0.053750, 0.050000, 0.066250, 0.820000
    };

const GLfloat ObsidianDiffuse [4] =
    {
        0.182750, 0.170000, 0.225250, 0.820000
    };

const GLfloat ObsidianSpecular [4] =
    {
        0.332741, 0.328634, 0.346435, 0.820000
    };

const GLfloat ObsidianShininess = 38.4;

// per≥a

const GLfloat PearlAmbient [4] =
    {
        0.250000, 0.207250, 0.207250, 0.922000
    };

const GLfloat PearlDiffuse [4] =
    {
        1.000000, 0.829000, 0.829000, 0.922000
    };

const GLfloat PearlSpecular [4] =
    {
        0.296648, 0.296648, 0.296648, 0.922000
    };

const GLfloat PearlShininess = 11.264;

// rubin

const GLfloat RubyAmbient [4] =
    {
        0.174500, 0.011750, 0.011750, 0.550000
    };

const GLfloat RubyDiffuse [4] =
    {
        0.614240, 0.041360, 0.041360, 0.550000
    };

const GLfloat RubySpecular [4] =
    {
        0.727811, 0.626959, 0.626959, 0.550000
    };

const GLfloat RubyShininess = 76.8;

// turkus

const GLfloat TurquoiseAmbient [4] =
    {
        0.100000, 0.187250, 0.174500, 0.800000
    };

const GLfloat TurquoiseDiffuse [4] =
    {
        0.396000, 0.741510, 0.691020, 0.800000
    };

const GLfloat TurquoiseSpecular [4] =
    {
        0.297254, 0.308290, 0.306678, 0.800000
    };

const GLfloat TurquoiseShininess = 12.8;

// czarny plastik

const GLfloat BlackPlasticAmbient [4] =
    {
        0.000000, 0.000000, 0.000000, 1.000000
    };

const GLfloat BlackPlasticDiffuse [4] =
    {
        0.010000, 0.010000, 0.010000, 1.000000
    };

const GLfloat BlackPlasticSpecular [4] =
    {
        0.500000, 0.500000, 0.500000, 1.000000
    };

const GLfloat BlackPlasticShininess = 32;

// czarna guma

const GLfloat BlackRubberAmbient [4] =
    {
        0.020000, 0.020000, 0.020000, 1.000000
    };

const GLfloat BlackRubberDiffuse [4] =
    {
        0.010000, 0.010000, 0.010000, 1.000000
    };

const GLfloat BlackRubberSpecular [4] =
    {
        0.040000, 0.040000, 0.040000, 1.000000
    };

const GLfloat BlackRubberShininess = 10;

#endif // __MATERIALS_H__
