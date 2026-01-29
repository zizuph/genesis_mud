/* A random marh.
 * Fysix@Genesis, August 1997
 */

inherit "/d/Gondor/std/steed/marh.c";

#include <ss_types.h>

#define R(x) random(x)

void
create_marh()
{
int   i = random(3);

   switch (i)
   {
    case 0:
      set_adj(({"tall", "strong"}));
      set_pshort("tall strong mearas");
      set_long("This is a tall strong marh. " +
         "Her white manes are long and she has bright flaming eyes. " +
         "Her body is tall and powerful, yet she is very agile. " +
         "\n");
      set_stats(({140 + R(20), 130 + R(15), 150 + R(20), 80, 80, 100 + R(10)}));
      set_skill(SS_UNARM_COMBAT, 50 + R(10));
      set_skill(SS_DEFENSE, 50 + R(10));
      set_skill(SS_BLIND_COMBAT, 50 + R(10));
      set_alignment(300 + R(100));
      set_gender(1);
      break;
    case 1:
      set_adj(({"old", "brown"}));
      set_pshort("old brown mearas");
      set_long("This is an old brown marh. " +
         "Though he is old, he has not lost anything of his vitality or " +
         "wildness. " +
         "Grey manes rest on his beautiful brown body. " +
         "\n");
      set_stats(({130 + R(20), 120 + R(15), 140 + R(20), 80, 80, 95 + R(10)}));
      set_skill(SS_UNARM_COMBAT, 45 + R(10));
      set_skill(SS_DEFENSE, 45 + R(10));
      set_skill(SS_BLIND_COMBAT, 45 + R(10));
      set_alignment(270 + R(100));
      set_gender(0);
      break;
    case 2:
      set_adj(({"young", "swift"}));
      set_pshort("young swift mearas");
      set_long("This is a young swift marh. " +
         "His slender body is not full-grown yet but it is well built, "+
         "with long legs carrying it. " +
         "His dark eyes are bright and are restlessly looking around. " +
         "\n");
      set_stats(({120 + R(20), 160 + R(15), 120 + R(20), 70, 70, 90 + R(10)}));
      set_skill(SS_UNARM_COMBAT, 40 + R(10));
      set_skill(SS_DEFENSE, 40 + R(10));
      set_skill(SS_BLIND_COMBAT, 40 + R(10));
      set_alignment(250 + R(100));
      set_gender(0);
      break;
   }
}
