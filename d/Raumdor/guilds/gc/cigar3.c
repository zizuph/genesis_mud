/*********************************************************************
 * - cigar3.c                                                      - *
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
  add_name("morgul royale");
  set_adj(({"dark", "slender"}));
  
  set_short("dark slender cigar");
  set_pshort("dark slender cigars");
  set_long("This "+ short() +" is known as a 'Morgul Royale'. The "+
    "tobacco is quite dark and comes from some of the darkest forests "+
    "that should not even be mentioned. The leaves have been soaked in "+
    "elven blood and dried. The process of this soaking and drying is "+
    "done twice to increase the flavour of the tobacco before it is "+
    "rolled into this fine cigar. You can <light cigar> to enjoy it's "+
    "unique flavour.\n");
   
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 185);

  seteuid(getuid(TO));
}

void
inhale()
{
  switch(random(400) % 4)
  {
    case 0:
        write("You inhale the smoke from your Morgul Royale cigar "+
          "and the distinct aroma of elven blood fills the air and "+
          "your lungs.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and "+
          "creates strange images of what appears to be tortured "+
          "elves out of smoke.\n");
        return;
    case 1:
        write("You inhale the smoke from your Morgul Royale cigar and "+
          "the remarkable aroma of elven blood reminds you of days "+
          "torturing elves.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and "+
          "creates what appears to be ringlets of shackles from smoke.\n");
        return;
    case 2:
        write("You inhale the smoke from your Morgul Royale cigar and the "+
          "uncommon aroma of elven blood is intoxicating.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and "+
          "creates an image of a tortured elven face with perfect rings "+
          "of smoke.\n");
        return;
    case 3:
        write("You puff on your Morgul Royale cigar and the unique aroma "+
          "of elven blood brings a flood of morbid thoughts accompanied "+
          "with tortured elves.\n");
        say(QCTNAME(TP)+" smokes on "+HIS(TP)+" "+ short() +" and "+
          "creates a perfectly aligned solid ring of smoke.\n");
        return;
   }
}

void
finish()
{
  write("You take the last smoke on this startling Morgul Royale cigar "+
    "then you put it out by placing it into the palm of your hand and "+
    "grinding it in until you are sure it no longer lit.\n"+
    "You then drop it to the ground dismissing it without another thought.\n");
  say(QCTNAME(TP)+" takes "+HIS(TP)+" last smoke on the "+ short() +", "+
    "then grinds it into "+HIS(TP)+" palm making sure it isn't "+
    "lit before dropping to ground.\n");
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
  write("You light your Morgul Royale cigar and start to inhale "+
    "the reeking elven blood smoke.\n");
  say(QCTNAME(TP)+" lights a "+ short() +" looking very pleased and "+
    "somehow distorted.\n");
    gLit = 1;
  set_alarm(20.0, 20.0, inhale);
  set_alarm(139.0,  0.0, finish);

  return 1;
}
int
do_smell(string arg)
{
    notify_fail("Smell what?\n");

    if(arg == "cigar" || arg == "morgul royale" || arg == "morgul royale cigar" 
        || arg == "dark slender cigar")
    {
        write("You bring the "+ short() +" up to your nose and inhale "+
        "deeply.\n\n"+
        "The strong scent of the "+ short() +" fills your senses. It "+
        "brings with it a feeling of shadows and unspeakable thoughts "+
        "intertwined with elven blood.\n");
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
