/*********************************************************************
 * - cigar1.c                                                      - *
 * - Cigar for Gentlemens club                                     - *
 * - Created by Damaris@Genesis 1/2003                             - *
 * - Debugged by Sarr 1/2003                                       - *
 *********************************************************************/
#pragma strict_types

#include "/d/Raumdor/defs.h"
#include <macros.h>
#include <cmdparse.h>
inherit "/std/object";

int gLit = 0;
void
create_object()
{
  set_name("cigar");
  add_name("shire sweet");
  set_adj(({"full", "flavoured"}));
  
  set_short("full flavoured cigar");
  set_pshort("full flavoured cigars");
  set_long("This "+ short() +" is known as a 'Shire Sweet'. "+
    "It has been made from the finest tobacco known in the Shire. "+
    "The leaves were still quite tender and full of sweet flavour "+
    "when they were rolled into this fine cigar. This pleasant "+ short() +" "+
    "has been imported special from Longbottom in the Southfarthing. "+
    "You can <light cigar> to enjoy it's spectacular flavour.\n");
   
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 125);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Shire Sweet cigar, "+
          "marveling at its wonderful sweet taste.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "soft almost perfect rings of smoke.\n");
        return;
    case 1:
        write("You puff on your Shire Sweet cigar, amazed "+
          "at its superb fresh taste.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "almost tranquil rings of smoke.\n");
        return;
    case 2:
        write("You inhale slowly from your Shire Sweet cigar, surprised "+
        "at its outstanding clean taste.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "soft puff rings of smoke.\n");
        return;
    case 3:
        write("You puff on your Shire Sweet cigar, amazed at "+
          "its dazzling pure sweet taste. This makes you feel peaceful and "+
          "calm as if you were lying back in a green field in the Shire.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "soft puffs of smoke.\n");
        return;
   }
}

void
finish()
{
  write("You take the last smoke on this fine Shire Sweet cigar then you "+
    "put it out by stomping it into the ground making sure it isn't still "+
    "lit.\n");
  say(QCTNAME(TP)+" takes "+HIS(TP)+" last smoke on the "+ short() +", "+
    "then stomps it into the ground making sure it isn't lit.\n");
  remove_object();
}

int
smoking(string str)
{
    object *obs;
    object cigar;

    NF("Smoke what?\n");

    if(!strlen(str))
        return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if(!sizeof(obs))
        return 0;
  
    NF("You can only smoke one cigar at a time!\n");
     if(sizeof(obs) > 1)
        return 0;

    cigar = obs[0];

    NF("You can't smoke that!\n");
    if(cigar != TO)
        return 0;

    NF("It is already lit!\n");
    if(gLit == 1)
        return 0;
  write("You light your Shire Sweet full flavoured cigar "+
    "and start to inhale the lovely sweet smoke.\n");
  say(QCTNAME(TP)+" lights a "+ short() +" looking very pleased and "+
    "relaxed.\n");
    gLit = 1;
  set_alarm(20.0, 20.0, inhale);
  set_alarm(139.0,  0.0, finish);

  return 1;
}

int
do_smell(string arg)
{
    notify_fail("Smell what?\n");

    if(arg == "cigar" || arg == "shire sweet" || arg == "shire sweet cigar" 
        || arg == "full flavoured cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The strong scent of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of warmth and peace.\n");
        say(QCTNAME(TP)+" smells the "+ short() +" deeply.\n");

        return 1;
    }

    return 0;
}



void
init()
{
  ::init();
  
    add_action(smoking, "smoke");
    add_action(smoking, "light");
    add_action(do_smell, "smell");

}

