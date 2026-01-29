/* Sarr of Kalad */
/* The Shadow Walker's Fire Special */

inherit "/std/object";

#include "/d/Kalad/defs.h"

#define KALAD_SHADOW_FIRE_ROOM "_kalad_shadow_fire_room"

int has_spread = 0;
object *runsa = ({});
int f_str;

void
set_fire_str(int i)
{
    f_str = i;
}

int
chance_to_spread()
{
    if(f_str > 185)
        return 60;
    if(f_str > 165)
        return 50;
    if(f_str > 115)
        return 40;
    if(f_str > 85)
        return 30;
    if(f_str > 55)
        return 20;
    if(f_str > 25)
        return 10;
}

string
query_fire_str()
{
    if(f_str > 185)
        return "lethal";
    if(f_str > 165)
        return "gigantic";
    if(f_str > 115)
        return "large";
    if(f_str >  85)
        return "medium-sized";
    if(f_str >  55)
        return "fair-sized";
    if(f_str >  25)
        return "small";
    return "puny";
}

void
create_object()
{
   set_name("fire");
   add_name("flame");
   set_adj("blazing");
   set_short("@@query_fire_str@@ blazing fire");
   set_long("A blazing fire that spreads everywhere. It is hot here! "+
   "The flames lick and burn at you. You best get out of here quick.\n");
   add_prop(OBJ_I_WEIGHT, 20000);
add_prop(OBJ_I_LIGHT,2);
   add_prop(OBJ_I_VOLUME, 200000);
   add_prop(OBJ_M_NO_GET, "You cannot take a fire!.\n");
   add_prop(OBJ_I_RES_FIRE, 100);
   add_prop("_sarr_acid_is_main_cloud",1);   
   set_alarm(10.0,10.0, "hurt_everyone_around");
   set_alarm(62.0,0.0, "evapourate");
}

void
evapourate()
{
   int i;
   this_object()->change_prop(CONT_I_NO_REM, 0);
   tell_room(environment(this_object()), "The fire finally "+
      "dies down slowly.\n");
   if(sizeof(runsa))
   {
       for(i=0;i<sizeof(runsa);i++)
       {
           if(runsa[i])
           {
           tell_room(E(runsa[i]),QCTNAME(runsa[i])+" runs back to "+
           HIS(runsa[i])+" post.\n");
           runsa[i]->move_living("M",runsa[i]->query_prop(KALAD_SHADOW_FIRE_ROOM));
           tell_room(E(runsa[i]),QCTNAME(runsa[i])+" arrives.\n");
           runsa[i]->remove_prop(KALAD_SHADOW_FIRE_ROOM);
           }
       }
   }
   this_object()->remove_object();
}


void
hurt_it(object livin)
{
    object co;
    int hitp;
    string strh;
    co = livin->query_combat_object();
    hitp = -f_str;

    /* A chance to avoid the fire */
    if(MIN(120,livin->query_stat(1)) > random(350)) 
    {
        tell_room(E(livin),QCTNAME(livin)+" dodges the "+
        "flames and avoids being burned.\n",livin);
        tell_object(livin,"You dodge the flames and avoid "+
        "being burned!\n");
        return;
    }
    /* Don't harm the newbies */
    if(livin->query_average_stat() <= 30 && interactive(livin))
    {
        tell_object(livin,"You are too small to be affected.\n");
        tell_room(E(livin),QCTNAME(livin)+" is too small to be "+
        "affected.\n",livin);
        return;
    }

    /*hitpoint modifier on RES_FIRE */

    if(livin->query_prop(MAGIC_I_RES_FIRE))
        hitp += (hitp/100) * livin->query_prop(MAGIC_I_RES_FIRE);
   
    /* Nothing happens to npcs with OBJ_M_NO_ATTACK */
    if(livin->query_prop(OBJ_M_NO_ATTACK))
    {
        tell_room(E(livin),QCTNAME(livin)+" resists the flames with "+
        "sheer will alone!\n");
        return;
    }  
    /* If you have enough resistance, you don't get burned. */
    if (hitp >= 0)
    {
        hitp = 0;
        tell_object(livin,"You are not affected by the flames.\n");
        tell_room(E(livin),QCTNAME(livin)+" is not affected by the "+
        "flames.\n");
        return;
    }
    else
    {
        if (hitp > -100)
            strh = "a little ";
        else if (hitp > -140)
            strh = "partly ";
        else if (hitp > -180)
            strh = "badly ";
        else
            strh = "very badly ";
        tell_object(livin,"You are burnt "+strh+"by the flames.\n");
        tell_room(E(livin),QCTNAME(livin)+" toasts in the fire.\n",livin);
    }
 
    livin->heal_hp(hitp);
    co->cb_add_panic(-hitp / 4);
    if (livin->query_hp() <= 0)
        livin->do_die(this_object());

    /* Run these checks for npcs only....players can move out of danger */
    /* on their own. */
    
    if(!livin) /* Did it die? */
        return;  
    if(livin->query_npc())
    {
        tell_room(E(livin),QCTNAME(livin)+" runs away from the fire!.\n");
        /* Add this check, so that it can return when the fire is out */
        if(!livin->query_prop(KALAD_SHADOW_FIRE_ROOM))
        {
            livin->add_prop(KALAD_SHADOW_FIRE_ROOM,file_name(E(livin)));
            runsa = runsa + ({livin});
        }
        livin->run_away();
    }
    
}

void
hurt_everyone_around()
{
   int i;
   object *things;
   mixed *exits;
   object cloud;
   seteuid(getuid(this_object()));
   things = FILTER_LIVE(all_inventory(environment(this_object())));
   for(i=0;i<sizeof(things);i++)
   {
       hurt_it(things[i]);
   }
   if (chance_to_spread() < random(100) ) /* Check if it spreads */
       return;
   /* let the fire spread out to all exits */
   if(query_prop("_sarr_acid_is_main_cloud") == 0) return; /* let only main cloud spread */
   /* ok, lets spread it */
   if(has_spread) return;
   has_spread = 1;
   exits = E(TO)->query_exit();
   if(!sizeof(exits))
   {
      return;
   }
   for (i=0;i<sizeof(exits);i+=3)
   {
      cloud = clone_object("/d/Kalad/common/guilds/shadow_walkers/fire");
      cloud->set_fire_str(f_str);
      cloud->add_prop("_sarr_acid_is_main_cloud",0);
      cloud->move(exits[i]);
      tell_room(E(cloud),"A "+cloud->short()+" starts up!\n");
   }
      tell_room(E(TO),"The "+short()+" spreads further out.\n");
}

