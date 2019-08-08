#ifndef COMMUN_H
#define COMMUN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NB_PIOCHE 10
#define PROB_AUGMENTATION_RARE_EPIQUE 100 / 25 // Probabilité de piocher une rare sur une pioche commune ou une épique sur une pioche rare (CF règles HEROES) (ex: 25% ==> 100 / 25)

const char* Pioches[NB_PIOCHE][2];/* = {{"héros communs", "1"}, {"héros rares force", "2"}, {"héros rares détermination", "3"}, {"héros rares charisme", "4"},
        {"héros épique charisme", "7"}, {"chances", "8"}, {"pièges", "9"}, {"vilains", "10"}};*/

#endif
