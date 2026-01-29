inherit "/std/object";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h";

create_object() {
  set_short("battered piece of paper");
  set_pshort("battered pieces of paper");
  set_long("@@describe");
  set_name(({"note"}));
  add_name(({"notes","piece of paper","paper"}));
  set_adj("battered");
  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE,0);
  add_prop("_gilraen_wolfcave_quest_note",1);
}

string describe() {
    return "\n"+
    BSN("After the attack had begun, I managed to grab a chest and some "+
        "bags, and attempted to escape, so that I might bring "+
        "word of the attack and some of our possessions to Minas Tirith "+
        "and my family. I fear I have failed however for as I crawl about "+
        "these dismal caves, I hear sounds of pursuit and wild animals. "+
        "I wonder which shall find me first. Ah, it matters not, one more "+
        "passageway and I shall hide the last of my burdens and attempt "+
        "yet another escape.");
}

init()
{
  add_action("read_note","read");
}

read_note(string str)
{
  if (!str) return 0;
  if (str != "note" && str != "paper") return 0;
  write(describe());
  return 1;
}
