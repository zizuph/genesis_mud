/*********************************************************************
 * - cigar5.c                                                      - *
 * - Cigar for Gentlemens club                                     - *
 * - Created by Damaris@Genesis 1/2003                             - *
 * - Kender Booty compliments of Misery 1/2003 ;)                  - *
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
  add_name("kender booty");
  set_adj(({"diverse", "flavoured"}));

  set_short("diverse flavoured cigar");
  set_pshort("diverse flavoured cigars");
  set_long("This "+ short() +" is known as a 'Kender Booty'. The "+
    "leaves are an assortment of premium tobacco borrowed from all "+
    "corners of the realms. Great care has been taken to blend the "+
    "medley of leaves, producing a curious, distinctive flavour. "+
    "You may <light cigar> to enjoy it's unique flavour.\n");

  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 150);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Kender Booty cigar, "+
          "marveling at its wonderfully unique taste.\n");
        say(QCTNAME(TP)+" puffs on "+HIS(TP)+" "+ short() +" and "+
          "creates fanciful rings of smoke.\n");
        return;
    case 1:
        write("You puff on your Kender Booty cigar, amazed at the "+
          "exceptional rich taste.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and "+
          "creates a rapid chain of smoke rings.\n");
        return;
    case 2:
        write("As you inhale slowly from your Kender Booty cigar, "+
          "visions of baubles dance through your head.\n");
        say(QCTNAME(TP)+" puffs on "+HIS(TP)+" "+ short() +" and "+
          "creates intricate patterns of smoke rings.\n");
        return;
    case 3:
        write("You puff on your Kender Booty cigar, astonished at the "+
          "curious blend of flavours. You feel exhilirated and fidgety "+
          "as if you were inspired to travel.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and blows "+
          "a clever series of smoke rings.\n");
        return;
   }
}

void
finish()
{
  write("You take one last drag of your Kender Booty cigar then you "+
    "put it out by stomping it into the ground making sure it isn't "+
    "still lit.\n");
  say(QCTNAME(TP)+" takes "+HIS(TP)+" last drag on the "+ short() +", "+
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
  write("You light your diverse flavoured Kender Booty cigar and start "+
    "to inhale the rich, flavourful smoke.\n");
  say(QCTNAME(TP)+" lights a "+ short() +" looking delighted and "+
    "cheery.\n");
    gLit = 1;
  set_alarm(20.0, 20.0, inhale);
  set_alarm(139.0,  0.0, finish);

  return 1;
}

int
do_smell(string arg)
{
    notify_fail("Smell what?\n");

    if(arg == "cigar" || arg == "kender booty" || arg == "kender booty cigar"
        || arg == "diverse flavoured cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The rousing aroma of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of wanderlust and adventure.\n");
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

