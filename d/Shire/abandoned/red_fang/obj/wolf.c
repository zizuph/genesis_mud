inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#include <tasks.h>
#include <cmdparse.h>

// PROPS 

#define WOLF_SUBLOC "_fang_wolf_subloc"
#define WOLF_I_RIDING "_wolf_i_riding"

// Globals-----------

string owner; // The owner
object rider; // The rider

int dismount(object ob); // The dismount function
int mount_the_wolf(object ob); // Called to move the wolf
object query_occupied(); // Who is on it ?
void set_occupied(object ob); // Set someone on it
void set_owner(object ob); // Set name for someone as owner
string query_owner(); // Return name of owner

void 
set_occupied(mixed ob)
{
    rider = ob;
}


mixed
query_occupied()
{
    return rider;
}


void 
set_owner(object ob)
{
    owner = ob->query_real_name();
}

string
query_owner()
{
    return owner;
}

// Show that we are riding the wolf

string
show_subloc(string subloc, object me, object for_ob)
{
     string str;
     if(!(subloc == WOLF_SUBLOC))
         return "";
     if(me == for_ob)
         str = "You are ";
     else
         str = C(HE(me))+" is ";
    return str+"riding a "+short()+".\n";
}



// Set the description of the wolf.

void
set_wolf_desc(string adj1, string adj2)
{
    if(stringp(adj1))
        add_adj(adj1);
    if(stringp(adj2))
        add_adj(adj2);
    if(stringp(adj1))
        set_short(adj1+" wolf");
    if(stringp(adj1) && strlen(adj2))
        set_short(adj1+" "+adj2+" wolf");
}

// We will configure the wolf here, depending on player (me)

int
configure_wolf(object me)
{
    string adjs,ad1,ad2;
    mapping temp = ([]);
    temp = restore_map(FANG_DIR(doc/wolf_log));
    adjs = temp[me->query_real_name()];
    if(!stringp(adjs))
        return 0;
    sscanf(adjs,"%s|%s",ad1,ad2);
    set_wolf_desc(ad1,ad2);
    set_owner(me);
    return 1;
}

void
save_wolf()
{
    string adjline,*adjs;
    mapping temp = ([]);
    adjs = query_adj(1);
    if(stringp(adjs[0]))
        adjline = adjs[0]+"|";
    if(sizeof(adjs) > 1 && stringp(adjs[1]))
        adjline += adjs[1];    
    temp = restore_map(FANG_DIR(doc/wolf_log));
    temp += ([query_owner():adjline]);
    save_map(temp,FANG_DIR(doc/wolf_log));
}

// Create the wolf here.

void
create_monster()
{
   ::create_monster();
   set_name("wolf"); 
   set_race_name("wolf");
   set_long("This is a strong and ferocious looking wolf. Breed by "+
   "goblins as a steed, it looks quite powerful. Only goblins would "+
   "know how to ride such a creature. It growls and stares at you "+
   "with fierce blood-shot eyes. If you are skilled, perhaps you can "+
   "'mount' it and move around. If it gets tired or hungry, you can "+
   "give it food and it will eat it. Try wolfhelp for more info.\n");
   set_stats(({120,120,120,20,20,100})); // Default stats
   add_prop(LIVE_I_NEVERKNOWN,1); 
   remove_prop(NPC_M_NO_ACCEPT_GIVE); // To give it food
   set_stuffed(500); /* Fill up on creation */
}


public void
init_living()
{
   ::init_living();
   add_action("do_mount","mount");
   add_action("do_dismount","dismount");
   if(present(TO,TP))
   {
       add_action("do_emote5","wolfpet");
       add_action("do_emote1","wolfsnarl");
       add_action("do_emote2","wolfhowl");
       add_action("do_emote3","wolfdrool");
       add_action("do_emote4","wolfcircle");
   }
   add_action("do_help","wolfhelp");
}

int
do_help()
{
    write("-----------------------------------\n");
    write("| The wolf will allow you to take |\n");
    write("| no fatigue while moving around. |\n");
    write("| However it won't help you in    |\n");
    write("| combat.                         |\n");
    write("| Some emotes:                    |\n");
    write("| wolfpet                         |\n");
    write("| wolfsnarl                       |\n");
    write("| wolfhowl                        |\n");
    write("| wolfdrool                       |\n");
    write("| wolfcircle                      |\n");
    write("-----------------------------------\n");
    return 1;
}

int
do_emote5()
{
    tell_room(E(TP),QCTNAME(TP)+" pets "+HIS(TP)+" "+short()+".\n",TP);
    write("You pet your "+short()+".\n");
    tell_room(E(TP),"The "+short()+" barks happily.\n");
    return 1;
}

int
do_emote1()
{
    tell_room(E(TP),"The "+short()+" mounted by "+QCTNAME(TP)+
    " snarls at you.\n",TP);
    write("Your "+short()+" snarls at everyone.\n");
    return 1;
}

int
do_emote2()
{
    tell_room(E(TP),"The "+short()+" howls at the moon.\n");
    return 1;
}

int
do_emote3()
{
    tell_room(E(TP),"The "+short()+" mounted by "+QCTNAME(TP)+
    " drools onto the ground, growling softly.\n",TP);
    write("Your "+short()+" drools onto the ground, growling "+
    "softly.\n");
    return 1;
}

// This function is way too long and complicated for its purpose, 
// I will make it more compact later when I have time ;-)

int
do_emote4(string str)
{
    int i;
    object *plays; 
    object *nosend;
    object target;
    plays = FILTER_LIVE(all_inventory(E(TP)));
    NF("Make the wolf circle whom?\n");
    if(!str)
        return 0;
    for(i=0;i<sizeof(plays);i++)
    {
        if(lower_case(plays[i]->query_name()) == str)
        {
            target = plays[i];
            break;
        }
        if(plays[i]->query_race_name() == str)
        {
            target = plays[i];
            break;
        }
        if(plays[i]->query_adj()+" "+plays[i]->query_race_name() == str)
        {
            target = plays[i];
            break;
        }
    }
        NF("You see no "+str+".\n");
        if(!target)
            return 0;
        nosend = ({target,TP});
        if(target->query_npc)
        {
        TP->catch_msg("You circle "+QTNAME(target)+" with your "+
        short()+" cautiously.\n");
        tell_room(E(TP),QCTNAME(TP)+" circles "+QTNAME(target)+
        " with "+HIS(TP)+" "+short()+" cautiously.\n",nosend);
        }
        else
        {
        TP->catch_msg("You circle "+QCTNAME(target)+" with your "+short()+
        " cautiously.\n");
        tell_room(E(TP),QCTNAME(TP)+" circles "+QCTNAME(target)+" with "+
        HIS(TP)+" "+short()+" cautiously.\n",nosend);
        }
        target->catch_msg(QCTNAME(TP)+" circles you with "+HIS(TP)+
        " "+short()+" "+
        "cautiously.\n");
        tell_room(E(TP),"The "+short()+" growls softly.\n");
        return 1;
}

// Check for leftovers

void
check_food()
{
    if(sizeof(all_inventory()))
        command("emote is all full now.");
    command("drop all");
}

// This will allow us to eat food and drink. Drop anything else.    
void
enter_inv(object ob, object from)
{
    int i,hn;
    object rid;

    if(objectp(rid = query_occupied()))
    {
        tell_object(rid,"You must dismount it before feeding it.\n");
        return;
    }

    if(function_exists("create_heap",ob) == FOOD_OBJECT)
    {
        hn = ob->num_heap();
        set_alarm(1.0,0.0,&command("eat all"));
        set_alarm(3.0,0.0,&check_food());
        return;
    }
    if(function_exists("create_heap",ob) == DRINK_OBJECT)
    { 
        hn = ob->num_heap();
        set_alarm(1.0,0.0,&command("drink all"));
        set_alarm(3.0,0.0,&check_food());
        return;
    }

    set_alarm(2.0,0.0,&command("drop all"));
    set_alarm(2.0,0.0,&command("emote doesn't want that."));
    return;
}


// This is the function that will allow us to mount up!

int
do_mount(string str)
{
    object who,wolfie,*list;
    NF("Mount what?\n");
    if (!str)
        return 0;
    NF("Mount which wolf?\n");
    list = FIND_STR_IN_OBJECT(str,E(TP));
    if(sizeof(list) > 1)
        return 0;
    if(!sizeof(list))
        return 0;
    wolfie = list[0];
    if( MASTER_OB(wolfie) != "/d/Kalad/common/guilds/red_fang/obj/wolf" )
        return 0;
    if(wolfie != TO) 
        return 0;
    // check if occupied
    if (objectp(who = query_occupied()) ) // Someone already on it?
    {
        who->catch_msg(QCTNAME(who)+" is on it already.\n");
        return 1;
    }
    // check if riding one already
    if(TP->query_prop(WOLF_I_RIDING))
    {
        write("You are already riding one!\n");
        return 1;
    }
    // Does one know how to ride it?
    if(TP->query_skill(SS_WOLF_RIDING) < 1)
    {
        write("You have no idea how to ride such a beast.\n");
        say(QCTNAME(TP)+" tries to mount a wolf, but has no idea how "+
        "to ride one.\n");
        return 1;
    }

    // If they fail to mount one....
    if(TP->resolve_task(TASK_ROUTINE,({TS_DEX,SS_WOLF_RIDING})) <= 0)
    {
        switch(random(3))
        {
            case 0:
            write("You try to mount the wolf, but fall off again. Perhaps "+
            "its time to improve your ability to ride wolves.\n");
            say(QCTNAME(TP)+" tries to mount the wolf but falls on "+
            TP->query_possessive()+" butt!\n");
            TP->command("blush");
            return 1;
            break;
            case 1:
            write("You accidentaly step on the wolf's foot while trying to "+
            "mount him, and he snarls at you and kicks you.  Ouch!!\n");
            write("Perhaps its time to improve your ability to ride wolves.\n");
            say(QCTNAME(TP)+" accidentaly steps on the wolf's foot while "+
            "trying to mount it, and it snarls at "+HIM(TP)+" and kicks "+
            HIM(TP)+".\n");
            TP->command("blush");
            return 1;
            break;
            case 2:
            write("You try to mount the ferocious wolf, but you accidentally "+
            "step over too far and fall down the other side.\n");
            write("Perhaps its time to improve some skill.\n");
            say(QCTNAME(TP)+" tries to mount the wolf, but accidentally "+
            "steps over too far and falls down the other side.\n");
            TP->command("blush");
            return 1;
            break;
        }
        return 1;
    }
    if(mount_the_wolf(TP))
        return 1;
    NF("Something went wrong.\n");
        return 0;
}

int
mount_the_wolf(object ob)
{
    object sh;
    // Add props to show we are on.
    ob->add_prop(WOLF_I_RIDING,1);
    ob->add_prop(LIVE_S_EXTRA_SHORT," riding a "+short());

    set_occupied(ob);

    // Make the wolf getable
    remove_prop(OBJ_M_NO_DROP); // So we can drop it when moving it out
    remove_prop(OBJ_M_NO_GET);
    change_prop(CONT_I_WEIGHT,0);
    change_prop(CONT_I_VOLUME,0);

    ob->add_subloc(WOLF_SUBLOC,TO);
    // Add shadow
    sh = clone_object("/d/Kalad/common/guilds/red_fang/obj/wolf_sh");
    sh->shadow_me(ob);
    sh->set_wolf(TO);

    tell_object(ob,"You mount the "+short()+".\n");
    tell_room(E(ob),QCTNAME(ob)+" mounts the "+short()+".\n",ob);

    move(TP);
    set_no_show();
    ob->add_prop(OBJ_M_NO_DROP,1); // Don't drop it.
    // Make it examinable to others
    TP->add_item("wolf","This is a strong and ferocious looking wolf. Breed by "+
    "goblins as a steed, it looks quite powerful. Only goblins would "+
    "know how to ride such a creature. It growls and stares at you "+
    "with fierce blood-shot eyes. "+QCTNAME(ob)+" is riding it.\n");
    return 1;
}

int 
do_dismount()
{
    if(dismount(TP))
    {
        write("You dismount the "+short()+".\n");
        say(QCTNAME(this_player())+" dismounts the "+short()+".\n");
        return 1;
    }
    return 0;
}

int
dismount(object ob)
{
    notify_fail("You are not riding one.\n");
    if(!ob->query_prop(WOLF_I_RIDING))
        return 0;
    if(query_occupied() != ob)
        return 0;

    ob->remove_prop(WOLF_I_RIDING);
    remove_prop(OBJ_M_NO_DROP);

    move(E(TP));

    set_occupied(0);    
    change_prop(CONT_I_WEIGHT,10000);
    change_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_M_NO_GET,1);
    
    unset_no_show();
    set_no_show_composite(0); 
    ob->remove_prop(LIVE_S_EXTRA_SHORT);

    ob->remove_item("wolf");
    ob->remove_subloc(WOLF_SUBLOC);
    
    ob->remove_wolf_shadow();

    return 1;
}
