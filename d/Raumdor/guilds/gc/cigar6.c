/*********************************************************************
 * - cigar6.c                                                      - *
 * - Cigar for Gentlemens club                                     - *
 * - Created by Damaris@Genesis 6/2003                             - *
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
  add_name("nobles classic");
  set_adj(({"cognac", "flavoured"}));
  
  set_short("cognac flavoured cigar");
  set_pshort("cognac flavoured cigars");
  set_long("This "+ short() +" is better known as a 'Nobles Classic'. "+
    "It has been made from the finest grown known in Drakmere. "+
    "The leaves were still quite young when they were soaked in a "+
    "cognac and dried. This drying process produces a pleasantly "+
    "strong cognac flavour in this fine cigar. This satisfying "+ short() +" "+
    "has been a specialty cigar for Noble Gentlemen in Drakmere "+
    "for quite some time. You can <light cigar> to enjoy it's "+
    "intense flavour.\n");
   
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 275);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Nobles Classic cigar "+
          "and the distinct aroma of special tobacco fills the air "+
          "and your lungs.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "strange images of what appears to be trees out of smoke.\n");
        return;
    case 1:
        write("You inhale the smoke from your Nobles Classic "+
          "cigar and the aroma of cognac and tobacco reminds "+
          "you of days sitting in the club discussing the "+
          "interests of the day.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "what appears to be a glass of cognac from the smoke.\n");
        return;
    case 2:
        write("You inhale the smoke from your Nobles Classic "+
          "cigar and the special aroma of tobacco and cognac "+
          "is relaxing.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "an image of a "+ short() +" with a solid stream of smoke.\n");
        return;
    case 3:
        write("You puff on your Nobles Classic cigar "+
          "and the exclusive aroma of cognac brings a flood of "+
          "melancholic thoughts as you watch a Noble float by.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "a perfectly aligned image of noble with a stream of smoke.\n");
        return;
   }
}

void
finish()
{
  write("You take the last smoke on this fine Nobles Classic cigar then you "+
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
  write("You light your Nobles Classic cognac flavoured cigar "+
    "and start to inhale the unusually cognac smoke.\n");
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

    if(arg == "cigar" || arg == "drakmere doobie" || arg == "drakmere doobie cigar" 
        || arg == "cognac flavoured cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The welcoming scent of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of relaxation.\n");
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

