/*********************************************************************
 * - cigar4.c                                                      - *
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
  add_name("drakmere doobie");
  set_adj(({"sweet", "flavoured"}));
  
  set_short("sweet flavoured cigar");
  set_pshort("sweet flavoured cigars");
  set_long("This "+ short() +" is known as a 'Drakmere Doobie'. "+
    "It has been made from the sweetest tobacco known in Drakmere. "+
    "The leaves were still quite young when they were soaked in a "+
    "special wine and dried. This drying process produces a pleasantly "+
    "strong sweet flavour in this fine cigar. This satisfying "+ short() +" "+
    "has been a specialty cigar for Gentlemen in Drakmere for quite some "+
    "time. You can <light cigar> to enjoy it's dramatic flavour.\n");
   
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 175);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Drakmere Doobie cigar "+
          "and the distinct aroma of special tobacco fills the air "+
          "and your lungs.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "strange images of what appears to be trees out of smoke.\n");
        return;
    case 1:
        write("You inhale the smoke from your Drakmere Doobie "+
          "cigar and the sweet aroma of tobacco and wine reminds "+
          "you of days frolicking in an open field.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "what appears to be a daisy from smoke.\n");
        return;
    case 2:
        write("You inhale the smoke from your Drakmere Doobie "+
          "cigar and the special aroma of tobacco and wine is enthralling.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "an image of a "+ short() +" with a solid stream of smoke.\n");
        return;
    case 3:
        write("You puff on your Drakmere Doobie cigar "+
          "and the exclusive aroma of wine brings a flood of "+
          "melancholic thoughts as you watch an elf float by.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and creates "+
          "a perfectly aligned image of an elf with a stream of smoke.\n");
        return;
   }
}

void
finish()
{
  write("You take the last smoke on this fine Drakmere Doobie cigar then you "+
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
  write("You light your Drakmere Doobie sweet flavoured cigar "+
    "and start to inhale the unusually sweet smoke.\n");
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
        || arg == "sweet flavoured cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The welcoming scent of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of hunger.\n");
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

