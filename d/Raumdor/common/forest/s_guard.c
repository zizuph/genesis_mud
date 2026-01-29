/* Giant Skeleton Warrior, Sarr */
#include "defs.h"
inherit STD_MONSTER;


void
create_monster() 
{
   ::create_monster();
   set_name("skeleton");
   set_race_name("skeleton");
   set_adj("guardian");
   set_short("guardian skeleton");
   set_long("@@my_long@@");
   set_gender(G_NEUTER);
   set_stats(({115,80,100,1,1,110}));
   set_skill(SS_DEFENCE,90);
   set_skill(SS_WEP_SWORD,95);
   set_skill(SS_WEP_POLEARM,95);
   set_skill(SS_WEP_KNIFE,95);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_SEE_DARK, 1);
   add_prop(OBJ_I_WEIGHT, 10000);
   add_prop(OBJ_I_VOLUME, 9000);
   add_prop(LIVE_I_UNDEAD,45);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_alignment(-450);
   set_act_time(3);
   add_act("emote smiles coldly.");
   set_cact_time(3);
   add_cact("emote lets out a silent scream of fury.");
   add_cact("emote wants to tear the flesh off you.");
   add_cact("emote mauls into you with a charge.");

    if (random(2))
        equip(({
          one_of_list(({
            COMMON_WEP_DIR + "cnaginata", COMMON_WEP_DIR + "ckatana",
            COMMON_WEP_DIR + "cwakizashi",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "rdplatemail", COMMON_ARM_DIR + "rtchainmail",
            COMMON_ARM_DIR + "rshelm",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "rfgreavs", COMMON_ARM_DIR + "rcbracers",
            COMMON_ARM_DIR + "kwboots",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "rdcloak", COMMON_ARM_DIR + "rbelt",
          })),
        }));
    else
        equip(({
          one_of_list(({
            COMMON_WEP_DIR + "cblsword", COMMON_WEP_DIR + "cbsword",
            COMMON_WEP_DIR + "cbdagger",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "kbplatemail", COMMON_ARM_DIR + "kbchainmail",
            COMMON_ARM_DIR + "kdhelm",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "kdgreavs", COMMON_ARM_DIR + "kbbracers",
            COMMON_ARM_DIR + "kwboots",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "ktcloak", COMMON_ARM_DIR + "ktgloves",
          })),
        }));
}

void
do_die(object killer)
{
     object bones;
     find_object(FOREST_DIR + "nforest15")->key_available();
     command("emote collapses to the ground.\nAs it hits the "+
     "ground, the key it was holding flies out of its hand and "+
     "into the waterfall!");
     bones = clone_object(COMMON_OBJ_DIR + "pbones");
     bones -> move(E(TO));
     ::do_die(killer);
}

string
my_long()
{
   return
   "This skeletal warrior looks like it comes right out of a nighmare. " +
   "Its evil flashing eyes, boney frame, and sharp skeletal claws invoke " +
   "a feeling of panic. This one is huge, making you wonder if this " +
   "one was once an ogre or a giant.\n" +
   "It holds a golden odd-shaped key in its hand.\n";
}
