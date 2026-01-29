
// file name: u_maker
// creator(s): Ilyian (31 August, 1995)
// last update:
// purpose: Creates Undead and populates the marsh with
//          them. Variables for the number of undead are
//          in dead.h  Note, there can never be more than
//          WRAITHS number of wraiths on the marshes at
//          one time.
// note: I used this method as an experiment in creating
//       monsters that are more linked together than most.
//       For example, if I wanted every wraith on the
//       marshed to scream when the banshee has been
//       killed, all I would have to do is do
//       i++; wraith[i]->command("scream");
//       Whereas cloning the monsters in each individual
//       would make this sort of connectedness impossible.
// bug(s):
// to-do: Add more connectedness to the monsters.
//        Make the Banshee and the Nightshade.

inherit "/d/Avenir/common/dead/dead";
#include "dead.h"

object *ghoul = allocate(GHOULS);
object *wraith = allocate(WRAITHS);
object *wight = allocate(WIGHTS);
object *spirit = allocate(SPIRITS);
object *apparition = allocate(APPARITIONS);
object *ghost = allocate(GHOSTS);

object banshee;

void
make_banshee(int chance)
{
  if(!banshee && random(9) < chance);
     {
       banshee = clone_object(MON+"banshee.c");
       banshee->move_living("M",PATH+"path8");
      }
}

void
make_wraiths(int chance)
{
 int i;
 for (i = 1; i < WRAITHS; i++)
  {
    if (random(9) < chance);
     {
      if (!wraith[i])
        {
          wraith[i] = clone_object(MON+"wraith.c");
          wraith[i]->arm_me();
          wraith[i]->move_living("M",MARSH+"marsh"+(random(65) + 1) );
         }
      }
    }
 }

void
make_ghouls(int chance)
{
 int i;
 for (i = 1; i < GHOULS; i++)
  {
    if (random(9) < chance);
     {
      if (!ghoul[i])
        {
          ghoul[i] = clone_object(MON+"ghoul.c");
          ghoul[i]->arm_me();
          ghoul[i]->move_living("M",MARSH+"marsh"+(random(65) + 1));
         }
      }
    }
 }

void
make_wights(int chance)
{
 int i;
 for (i = 1; i < WIGHTS; i++)
  {
    if (random(9) < chance);
     {
      if (!wight[i])
        {
          wight[i] = clone_object(MON+"wight.c");
          wight[i]->arm_me();
          wight[i]->move_living("M",MARSH+"marsh"+(random(65) + 1));
         }
      }
    }
 }

void
make_spirits(int chance)
{
 int i;
 for (i = 1; i < SPIRITS; i++)
  {
    if (random(9) < chance);
     {
      if (!spirit[i])
        {
          spirit[i] = clone_object(MON+"spirit.c");
          spirit[i]->arm_me();
          spirit[i]->move_living("M",MARSH+"marsh"+(random(65) + 1));
         }
      }
    }
 }

void
make_apparitions(int chance)
{
 int i;
 for (i = 1; i < APPARITIONS; i++)
  {
    if (random(9) < chance);
     {
      if (!apparition[i])
        {
          apparition[i] = clone_object(MON+"apparition.c");
          apparition[i]->arm_me();
          apparition[i]->move_living("M",MARSH+"marsh"+(random(65) + 1));
         }
      }
    }
 }


void
make_ghosts(int chance)
{
 int i;
 for (i = 1; i < GHOSTS; i++)
  {
    if (random(9) < chance);
     {
      if (!ghost[i])
        {
          ghost[i] = clone_object(MON+"ghost");
          ghost[i]->arm_me();
          ghost[i]->move_living("M",CRYPT+"crypt"+random(109));
         }
      }
    }
 }


create_room()
{
set_short("land of the undead");
set_long("You are in the land of the undead, where "
        +"spirits of the dead are reanimated into "
        +"hideous creatures.\nYou feel like you "
        +"should not be here at all.\n");


    add_prop(ROOM_I_NO_CLEANUP, 1);

}

void
start_cooking()
{
   set_alarm(5.0,0.0,&make_wraiths(10));
   set_alarm(10.0,0.0,&make_ghouls(10));
   set_alarm(15.0,0.0,&make_wights(10));
   set_alarm(20.0,0.0,&make_apparitions(10));
   set_alarm(25.0,0.0,&make_spirits(10));

//   set_alarm(30.0,0.0,&make_ghosts(10));

//   set_alarm(8.0,0.0,&make_banshee(10));

// make_nightshade(10);
}

reset_room()
 {
/* 50% chance that each wraith, wight, and ghoul will reset */
/* and spirit and apparition ... */
   set_alarm(2.0,0.0,&make_wraiths(5));
   set_alarm(5.0,0.0,&make_ghouls(5));
   set_alarm(8.0,0.0,&make_wights(5));
   set_alarm(11.0,0.0,&make_apparitions(5));
   set_alarm(14.0,0.0,&make_spirits(5));

//   set_alarm(17.0,0.0,&make_ghosts(5));
// Crypt not yet open...
 }


