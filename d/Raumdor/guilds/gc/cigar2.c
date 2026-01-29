/*********************************************************************
 * - cigar2.c                                                      - *
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
  add_name("calian classic");
  set_adj(({"smooth", "flavoured"}));

  set_short("smooth flavoured cigar");
  set_pshort("smooth flavoured cigars");
  set_long("This "+ short() +" is known as a 'Calian Classic'. "+
    "It has been made from the finest but quite rare tobacco known to "+
    "exist in the mid-western regions of Calia. The leaves are quite "+
    "smooth and full of a distinct aroma, which lends to its classic "+
    "taste and feel. You can <light cigar> to enjoy it's smooth "+
    "flavour.\n");

  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 155);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Calian Classic "+
          "cigar, enjoying its wonderfully smooth taste.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "a ring of smoke then blows another ring of smoke through "+
          "the first one.\n");
        return;
    case 1:
        write("You puff the smoke from your Calian Classic cigar, "+
          "appreciating its amazingly smooth taste reminding you of "+
          "days of fighting Kroug then relaxing in the pub after.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "soft smoke rings as if in deep thought.\n");
        return;
    case 2:
        write("You inhale the smoke from your Calian Classic "+
          "cigar and the distinct aroma of smooth tobacco fills "+
          "the air and your lungs.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "soft puffs of smoke.\n");
        return;
    case 3:
        write("You puff on your Calian Classic cigar and the unique "+
        "aroma seems to be quite intoxicating making you just a little "+
        "bit dizzy.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and looks "+
          "a little bit dizzy.\n");
        return;
   }
}

void
finish()
{
  write("You take the last smoke on this treasured Calian Classic "+
    "cigar then you put it out by stomping it into the ground "+
    "making sure it isn't still lit.\n");
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

  write("You light your Calian Classic "+ short() +" and start "+
    "to inhale the smooth aromatic smoke.\n");
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

    if(arg == "cigar" || arg == "calian classic" || arg == "calian classic cigar"
        || arg == "smooth flavoured cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The smooth scent of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of pride and peace.\n");
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

