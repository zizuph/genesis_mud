/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo in the error message for clear()
 *  Modified: 6 May 2003, by Bleys
 *      - Rewrote the swing() function, which was giving no
 *          return in some cases.
 *      - Changed stand() to accept "up" as an argument
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#define EV environment(TP)

inherit STDROOM;

inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


object person_sitting;
int sit(string str);
int swing(string str);
string push_swing();
int stand(string str);
int clear(string str);
int climb_swing(string str);
string rturn_you(object person);
int sitting = 0;
int nopath = 0;
void link_death_check();
void forced_stand(object person);
void still_here(object ob,object from);

#include <stdproperties.h>


public void
do_blow()
{
    if (nopath == 1)
    {
       tell_room(this_object(), "A gust of wind blows the snow " +
           "over the path hiding it from view.\n");
       add_item(("porch"),"The porch is blocked by heavy snowfall.\n");
       remove_exit("north");
       nopath = 0;
    }
    return;
}


public void
create_room()
{
    ::create_room();
    set_short("yard");
    set_long("@@change_long");

    add_item(({"swing","tree swing"}),"A tree swing " +
       "hangs from a low branch on the east oak tree.\n");
    add_item(({"oak tree","tree","trees"}),"Two old oak " +
       "trees grow on either side of the house. An old " +
       "swing can be seen hanging from the oak tree " +
       "to the east.\n");
    add_item(({"daub","waddle"}),"The wattle is twigs or " +
       "pieces of wood that create a framework " +
       "for the daub which is a mud and lye mixture.\n");
    add_item(("branch"),"A tree swing hangs on the old " +
       "oak tree.\n");
    add_item(({"thatch roof","roof"}),"The roof is of thatch " +
       "construction. It looks in big need of repair.\n");
    add_item(({"snow","snowfall"}),"A thick blanket of snow " +
       "covers everything.\n");
    add_item(({"window","window"}),"Covered in filth the windows " +
       "barely allow any light to pass through.\n");
    add_item(("porch"),"The porch is blocked by heavy snowfall.\n");
    add_item(("shadow"),"The large shadow is well hidden among " +
       "dense branches of the western oak tree. Its difficult " +
       "to determine what it is from this distance.\n");
    add_item(("grass"),"The grass looks frozen.\n");
    add_item(("yard"),"The yard looks unkempt.\n");
    add_item(({"small tree","small trees"}),"The small trees line the outer " +
       "property line of the yard.\n");

    add_exit(CALATHIN_DIR + "paths/path_w07","east","@@notifsitting");

    add_cmd_item("swing","push",push_swing);
    add_cmd_item("tree","climb",
       "The trunk of the tree is too wide to climb.\n");
    add_cmd_item(({"swing","tree swing"}),"climb",climb_swing);

    set_up_herbs( ({TER_HERB + "whitehorn"}),
                  ({"small tree","small trees"}) ,
                   3 );

    do_blow();

    reset_room();
}

void init()
{
    ::init();
       add_action(sit,"sit");
       add_action(swing,"swing");
       add_action(stand,"stand");
       add_action(clear,"dig");
       add_action("do_smell", "smell");
}


int
sit(string str)
{
    if( (str != "on swing") && (str != "on the swing") &&
        (str != "swing") )
    {
       notify_fail("Sit on what, the swing maybe?\n");
       return 0;
    }
     link_death_check();
       if(sitting == 0)
       {
          write ("You sit down on the swing.\n");
          say(QCTNAME(TP) + " sits on the swing.\n");
          sitting = 1;
        if(sitting == 1)
        {
        person_sitting = TP;
        person_sitting ->add_prop(LIVE_S_EXTRA_SHORT,
           " is sitting on a tree swing.\n");
        return 1;
        }
   }
       NF(QCTNAME(person_sitting) + " is already sitting on the swing.\n");
       return 0;
}


int
stand(string str)
{
    if((sitting == 1 && person_sitting == TP))
    {
       if(str != "up" && str != 0)
       {
          return 0;
       }
       write("You stop swinging and stand up from the swing.\n");
       say (QCTNAME(TP) + " stops swinging and stands up.\n");
       sitting = 0;
       person_sitting->remove_prop(LIVE_S_EXTRA_SHORT);
       person_sitting = 0;
       return 1;
     }
     notify_fail("You are already standing.\n");
     return 0;
}


int
swing(string str)
{

    if ( (str != "swing") && (str != 0) )
    {
        NF("Swing what?\n");
        return 0;
    }

    if ( person_sitting != TP )
    {
        NF("It might be easier to swing if you actually " +
           "sit on the swing first.\n");
        return 0;
    }

   write("You swing back and forth.\n");
   say(QCTNAME(TP) + " swings back and forth on the tree swing.\n");

    return 1;

}


string
rturn_you(object person)
{
   if(person == TP)
   {
      if(person == person_sitting)
      {
       return "you";
      }
    return "You";
   }
    return person->query_The_name(TP);
}



string
push_swing()
{

   if ((TP == person_sitting))
   {
      write("You cant push the swing while sitting on it!\n");
    return "";
   }
      if ((TP != person_sitting && sitting == 1))
      {
         write("You push " + rturn_you(person_sitting) + " on the swing.\n");
         say(QCTNAME(TP) + " pushes " + QCTNAME(person_sitting) +
            " back and forth on the tree swing.\n", ({TP,person_sitting}));
         person_sitting->catch_msg(QCTNAME(TP) + " pushes you back " +
            "and forth on the tree swing.\n");
      }
      if (sitting == 0)
      {
         write("You push an empty swing.\n");
         say(QCTNAME(TP) + " pushes an empty swing, wishing " + TP->query_pronoun() +
            " had someone to play with.\n");
      }
   return "";
}



int
clear(string str)
{
    if((str != "a path" && str != "through snow"))
    {
       notify_fail("Dig what, a path or through snow maybe?\n");
       return 0;
    }
       if((nopath == 0 && TP != person_sitting))
       {
             write("You clear a path through the snow to the front " +
             "porch.\n");
             say(QCTNAME(TP) + " clears a path through the snow.\n");
             nopath = 1;
             set_alarm(15.0, 0.0, do_blow);

             add_exit(CALATHIN_DIR + "houses/house3_porch","north","@@notifsitting");
             add_item(("porch"),"Someone dug a path through the snow " +
                "to the front porch.\n");

            write_file(TEREL_DIR + "log/clear_house3",
               TP->query_name()+" " + ctime(time()) + "\n");

            return 1;
       }
       notify_fail("You cant do that right now.\n");
       return 0;
}




int
climb_swing(string str)
{
   if (TP == person_sitting)
   {
      NF("You cant climb the swing while sitting on " +
        "it.\n");
     return 0;
   }
      if ((TP->query_skill(SS_CLIMB) > 29))
      {
         write("You shimmy up the tree swing.\n");
         TP->move_living("climbing up the swing",
         CALATHIN_DIR + "houses/house3_tree.c",1,0);
         return 1;
      }
         notify_fail("Climbing the swing looks too dangerous for you.\n");
         return 0;
}


int
notifsitting()
{
    if((sitting == 1 && person_sitting == TP))
    {
       write("You can't leave until you stand up!\n");
       return 1;
    }
    return 0;
}



string
change_long()
{
    link_death_check();
    if( nopath == 0 )
    {
       return "To the north is a small single level house. " +
              "As you approach the house you begin to notice " +
              "signs of negligence and disrepair. The daub has " +
              "cracked and fallen away in places revealing the " +
              "wattle underneath. The windows are so dirty that only " +
              "a dim light can be seen through them. The thatch roof is " +
              "not quite steep enough to shed the constant snowfall " +
              "and shows signs of sagging in the center. The snow has " +
              "piled up near the porch and the path is invisible " +
              "if indeed one even exists. Two old oak trees " +
              "grow on the west and east sides of the house while a " +
              "row of small trees line up against the property line.\n";
     }

     if( nopath == 1 )
        {
       return "To the north is a small single level house. " +
              "As you approach the house you begin to notice " +
              "signs of negligance and disrepair. The daub has " +
              "cracked and fallen away in places revealing the " +
              "wattle underneath. The windows are so dirty that only " +
              "a dim light can be seen through them. The thatch roof is " +
              "not quite steep enough to shed the constant snowfall " +
              "and shows signs of sagging in the center. Someone has " +
              "cleared a fresh path through the snow to the front porch. " +
              "Two old oak trees grow on the west and east sides of the house while a " +
              "row of small trees line up against the property line.\n";

       }

}


void
link_death_check()
{
    if(sitting == 1)
    {
       if(!person_sitting)
       {
          forced_stand(person_sitting);
          return;
       }
       still_here(person_sitting,environment(person_sitting));
       return;
     }
}


void
still_here(object ob, object from)
{
    if(from->query_short() != "yard")
    {
       forced_stand(ob);
    }
}


void
forced_stand(object person)
{
    sitting = 0;
    if(person == person_sitting)
    {
       person_sitting;
    }
}



/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */
public int
do_smell(string what)
{
    string poss, str, *smells;
    object *ob;
    int i;

    ob = all_inventory(TO);
    poss = POSSESSIVE(TP);
    smells = ({"cedar trees","smoke"});
    for (i = 0; i < sizeof(ob); i++) {
        if (living(ob[i]) && !ob[i]->query_wiz_level() && ob[i] != TP) {
            smells += ({QTNAME(ob[i])});
        }
    }
    str = "You inhale deeply through your nose, and recognise the " +
        "smell of ";
    TP->catch_msg(str + smells[random(sizeof(smells))] + ".\n");
    say(QCTNAME(TP) + " inhales deeply through " + poss + " nose.\n");
    return 1;
}


