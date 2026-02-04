inherit "/d/Terel/std/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

public string
age()
{
   string *ages;
   ages = ({"young", "old", "mature", "youthful",
          "elderly", "mystic", "noble"});
   return ages[random(sizeof(ages))];
}

public string
face()
{
   string *faces;
   faces = ({"fair", "melancholy", "happy", "cheerful", "imposing",
         "green-eyed", "silver-haired", "pious", "hazel-eyed",
         "gold-haired", "gallant", "poetic", "mischevious",
         "blue-eyed", "sorrowful", "dandyish"});
   return faces[random(sizeof(faces))];
}

public void
create_monster()
{
   set_race_name("elf");
   set_name("elf");
   set_pname("elves");
   set_short(age()+" "+face()+" elf");
   set_adj(age());
   add_adj(face());
   set_gender(random(3) -1);

   set_long("A virtuous elf. They keep magic " +
            "alive in the world. They are wondrous creatures.\n");

   set_base_stat(SS_STR, random(10)+4);
   set_base_stat(SS_DEX, 20);
   set_base_stat(SS_CON, 12);
   set_base_stat(SS_INT, 15);
   set_base_stat(SS_WIS, 20);
   set_base_stat(SS_DIS, 6);

   set_skill(SS_WEP_KNIFE, 4);
   set_random_move(2);
    add_prop(LIVE_I_NEVERKNOWN,1);

   set_all_hitloc_unarmed(10);
   set_all_attack_unarmed(random(10) + 5, random(5) + 10);

   set_chat_time(5);
   add_chat("Hail!");
   add_chat("Welcome to Calathin!");
   add_chat("Peace go with you.");
   add_chat("Seek the mystics of the valley for wisdom.");
   add_chat("Beware the orcs of the Silver Forest!");
   add_chat("It is said that the ruined mansion has many treasures.");
   add_chat("There is a witch living in the forest.");
   add_chat("The wolves have become very vicious.");

   set_act_time(7);
   add_act("@@dance_about");
   add_act("@@sing_song");
}

public string
dance_about()
{
   tell_room(environment(this_object()), QCTNAME(this_object()) +
             " dances about playfully.\n");
   return "";
}

public string
sing_song()
{
   tell_room(environment(this_object()), QCTNAME(this_object()) +
             " sings a beautiful song.\n");
   return "";
}
