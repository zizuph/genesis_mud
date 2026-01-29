 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
 
int times;
 
void
create_armour()
{
 
    set_name("shield");
    add_adj("obsidian");
    add_adj("black");
    set_long("This is a black obsidian shield. You have "+
             "never seen such a strange armour. It should provide "+
             "very good protection!\n"+
             "You manage to decipher some strange runes "+
             "inscribed on this shield!\n");
    set_short("black obsidian shield");
 
    set_ac(35);
 
    /*        impale, slash, bludgeon */
    set_am(({   1,     1,      1 }));
 
    set_at(A_SHIELD);
}
 
void init()
{
  add_action("do_cast","cast");
  add_action("do_read","read");
  add_action("do_exa","exa");
  add_action("do_exa","examine");
  add_action("do_exa","look");
  ::init();
}
 
int do_cast(string whatsp)
{
  object shadow;
  NF("Cast what?\n");
  if (whatsp!="protection") return 0;
  if (TP->shield_shadow_exist()==5)
    {
      write("You already have magical shield in effect!\n");
      return 1;
    }
  if (TP->query_mana()<100)
    {
      write("You are too exhausted to cast this spell!\n");
      return 1;
    }
  TP->add_mana(-100);
  if (TP->query_base_stat(SS_WIS)<(60+random(100)))
    {
      write("You fail to concentrate enough upon the spell !\n");
      return 1;
    }
  shadow=clone_object("/d/Rhovanion/paladin/camp/shield_shadow.c");
  shadow->shadow_me(TP);
  shadow->destruct_shield_shadow();
  return 1;
}
 
int do_read(string arg)
{
  NF("Read what ?\n");
  if ((arg!="rune")&&(arg!="runes")) return 0;
  write("You try to read these runes, but fail.\n"+
        "You examine them closer then...\n"+
        "Suddenly you feel that the last line of the runes "+
        "consist of a single word : 'protection' !\n"+
        "You don't know why do you think so, but you are sure "+
        "about that.\n"+
        "It should be a VERY powerful spell, maybe you can try "+
        "to cast it?\n");
  return 1;
}
 
int do_exa(string arg)
{
  NF("Examine what?\n");
  if ((arg!="rune")&&(arg!="runes")&&(arg!="at rune")&&(arg!="at runes"))
      return 0;
write("Very strange looking runes, maybe you should try to read it?\n");
  return 1;
}
 
