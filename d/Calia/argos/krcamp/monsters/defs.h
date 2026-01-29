#include "../areadefs.h"
#include "/d/Calia/argos/specials/teamsupt.c"
#include "../kenemy.h"
 
/* Some male adjectives for Kretan soldiers */
#define MaleAdj \
   ({"strong","muscular","blue-eyed","green-eyed","brown-eyed",     \
     "clean-shaven","brown-haired","blonde-haired","aggressive",    \
     "black-haired","black-eyed","young","stoical","brown-bearded", \
     "red-bearded","black-bearded","olive-skinned","virile",        \
     "broad-chested","confident","vigilant"})
 
/* mask function so doesn't attack incognito kretan players */
void aggressive_attack(object Tp) {
   if (!(kretan_enemy(Tp))) return;
   ::aggressive_attack(Tp);
}
