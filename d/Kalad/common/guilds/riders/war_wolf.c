inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include <tasks.h>

// PROPS 

#define WOLF_O_OCCUPIED "_wolf_o_occupied" 
#define WOLF_O_RIDING "_wolf_o_riding"
#define WOLF_SUBLOC "_fang_wolf_subloc"


// Globals-----------

string wadj1, wadj2; 

int dismount(object ob); // The dismount function

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

// Set the description of the wolf. We use 2 adjectives

void
set_wolf_desc(string adj1, string adj2)
{
    wadj1 = adj1;
    wadj2 = adj2;
    add_adj(adj1);
    add_adj(adj2);
    set_short(adj1+" "+adj2+" warwolf");
}

// This is used if only one adjective is used to describe wolf
void
set_wolf_desc_one(string adj1)
{
    wadj1 = adj1;
    add_adj(adj1);
    set_short(adj1+" warwolf");
}


// Create the wolf here.
void
create_monster()
{
   ::create_monster();
   set_name("warwolf"); 
   set_race_name("warwolf");
   set_long("This is a strong and ferocious looking wolf. Bred by "+
   "the Riders of the Red Fang to be agile, strong and very efficient "+
   "killers. Only Riders of the Red Fang could be able to handle this "+
   "massive beast. Perhaps it is the fact that it's the size of a small "+
   "horse, or maybe because its fangs are half a foot long, but something "+
   "about this wolf makes you want to run and hide. If it gets tired or "+
   "hungry, you can give it food and it will eat it. Try warhelp for more info.\n");
   set_stats(({160,120,150,50,50,130}));
   add_prop(LIVE_I_NEVERKNOWN,1); 
   remove_prop(NPC_M_NO_ACCEPT_GIVE); // To give it food
   remove_prop(OBJ_M_NO_DROP); // So we can drop it when moving it out
   set_stuffed(3500); /* Fill up on creation */
   set_alarm(10.0,60.0,"wolf_act");
}
int
wolf_act()
{
    string act;
    switch(random(14))
    {
        case 0:
        act = "growls softly in your direction.\n";
        break;
        case 1:
        act = "barks viciously, staring intently at you with malevolant eyes.\n";
        break;
        case 2:
        act = "begins to pant, splashing drool everywhere.\n";
        break;
        case 3:
        act = "growls savagely.\n";
        break; 
        case 4:
        act = "yawns tiredly, revealing long sharp deadly fangs.\n";
        break;
        case 5:
        act = "sniffs in your direction.\n";
        break;
        case 6:
        act = "curls it's lips up with a fearsome snarl, exposing it's deadly fangs.\n";
        break;
        case 7:
        act = "shifts it's massive wieght to one side, growling deeply.\n";
        break;
        case 8:
        act = "stretches it's paws, leaveing huge scratches in the ground from it's massive claws.\n";
        case 9:
        act = "peers around the room, looking for something to chew on.\n";
        break;
        case 10:
        act = "rumbles a low, deep growl.\n";
        break;
        case 11:
        act = "sniffs the ground, as if it where tracking something.\n";
        break;
        case 12:
        act = "taps its long, deadly claws on the ground, as it paces impatiently.\n";
        break; 
        case 13:
        act = "stares at you with it's peirceing, bloodlusting gaze.\n";
    }

    if(living(E(TO)))
        tell_room(E(E(TO)),"The "+short()+" "+act);
    else
        tell_room(E(TO),"The "+short()+" "+act);

    return 1;
}

public void
init_living()
{
   ::init_living();
   add_action("do_mount","mount");
   add_action("do_dismount","dismount");
   if(present(TO,TP))
   {
       add_action("do_emote6","warscare");
       add_action("do_emote5","warpet");
       add_action("do_emote1","warsnarl");
       add_action("do_emote2","warhowl");
       add_action("do_emote3","wardrool");
       add_action("do_emote4","warcircle");
   }
   add_action("do_help","warhelp");
}

int
do_help()
{
    write("-----------------------------------\n");
    write("| The wolf will allow you to take |\n");
    write("| no fatigue while moving around. |\n");
    write("| Some emotes:                    |\n");
    write("|     warpet                      |\n");
    write("|     warsnarl                    |\n");
    write("|     warhowl                     |\n");
    write("|     wardrool                    |\n");
    write("|     warcircle                   |\n");
    write("|     warscare                    |\n");
    write("| Combat Special:                 |\n");
    write("|     rslash <victem>             |\n");
    write("-----------------------------------\n");
    return 1;
}
int
do_emote6(string str)
{
    object *target;
    target = PARSE_THIS(str, "[the] %l");
    NF("warscare who?\n");
    if(!sizeof (target))
    return 0;
    target[0]->catch_msg(QCTNAME(TP)+" glares malevolantly at you "+HE(TP)+" pulls the harness on "+HIS(TP)+" massive wolf "+
        "sharply. The massive wolf suddenly rears up and lunges forward with a great "+
        "snarl and snaps it's massive jaw shut inches from your face!\n",TP);
        TP->catch_msg("You pull the harness sharply and make your massive wolf lunge "+
        "forward and snap it's jaw shut inches away from "+QTNAME(target[0])+"'s face!\n");
    tell_room(E(TP),QCTNAME(TP)+" glares malevolantly at "+QTNAME(target[0])+" as "+HE(TP)+" pulls the harness on "+HIS(TP)+" massive wolf "+
        "sharply. The massive wolf suddenly rears up and lunges forward with a great "+
        "snarl and snaps it's massive jaw shut inches from "+QTNAME(target[0])+"'s face!\n",({target[0],TP}));
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
    " snarls viciously at you.\n",TP);
    write("Your "+short()+" snarls at everyone viciously.\n");
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
    " drools onto the ground, growling viciously.\n",TP);
    write("Your "+short()+" drools onto the ground, growling "+
    "viciously.\n");
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
        tell_room(E(TP),"The "+short()+" growls viciously.\n");
        return 1;
}

// This will clean out our inventory, in case anything escaped 
// detection in the food eating function
void
clean_up()
{
    int i,j;
    object *obs = all_inventory();
    for(i=0;i<sizeof(obs);i++)
    {
        if(obs[i]->num_heap())
            for(j=0;j<obs[i]->num_heap();j++)
                set_alarm(1.0,0.0,&command("drop "+obs[i]->query_name()));
        else
            set_alarm(1.0,0.0,&command("drop "+obs[i]->query_name()));
            
    }
}

string
query_collar()
{
    object collar;
    collar = present("collar",TO);
    if(objectp(collar))
        return "\nIt is wearing a "+collar->short()+".\n";
    else
        return "\n";
}

// This will allow us to eat food and drink, and accept collars, it will drop anything else.    
void
enter_inv(object ob, object from)
{
    int i,hn;
    object rider;
    if(rider = query_prop(WOLF_O_OCCUPIED))
    {
        tell_object(rider,"You must dismount it before feeding it.\n");
        return;
    }
    if(ob->id("collar"))
    {
        command("wear collar");
        return;
    }
    if(function_exists("create_food",ob))
    {
        hn = ob->num_heap();
        set_alarm(1.0,0.0,&command("eat "+ob->query_name()+"s"));
        set_alarm(2.0,0.0,"clean_up");
        return;
    }
    if(function_exists("create_drink",ob))
    { 
        hn = ob->num_heap();
        set_alarm(1.0,0.0,&command("drink "+ob->query_name()+"s"));
        set_alarm(2.0,0.0,"clean_up");
        return;
    }
    set_alarm(1.0,0.0,&command("drop "+ob->query_name()));
    command("emote doesn't want that.");
    set_alarm(2.0,0.0,"clean_up");
    return;
}


// This is the function that will allow us to mount up!
int
do_mount(string str)
{
    object who,list,sh;
    NF("Mount what?\n");
    if (!str)
        return 0;
    if(!parse_command("mount "+str,E(TP),"'mount' %o",list))
        return 0;
    if(present(list,TP)) // Can't mount the wolf in us
        return 0;
    notify_fail("Can't find any "+str+" here.\n");
    if (!list) // Didn't find a wolf
        return 0;
    if(list != TO) // Not this wolf
        return 0;
    // check if occupied
    if (who = query_prop(WOLF_O_OCCUPIED)) // Someone already on it?
    {
        write(QCTNAME(who)+" is on it already.\n");
        return 1;
    }
    // check if riding one already
    if(TP->query_prop(WOLF_O_RIDING))
    {
        write("You are already riding one!\n");
        return 1;
    }
    // Does one know how to ride it?
 
    if(TP->query_skill(SS_WOLF_HANDLING || SS_WOLF_RIDING) < 1)
    {
        write("You have no idea how to ride nor handle a warwolf.\n");
        say(QCTNAME(TP)+" tries to mount a warwolf, but has no idea how "+
        "to ride one.\n");
        return 1;
    }
    // If they fail to mount one....
    if(TP->resolve_task(TASK_ROUTINE,({TS_DEX,SS_WOLF_RIDING})) <= 0)
    {
        switch(random(3))
        {
        case 0:
         write("You try to mount the warwolf, but fall off again. Perhaps "+
         "its time to improve your ability to ride or handle wolves.\n");
         say(QCTNAME(TP)+" tries to mount the warwolf but falls on "+
         TP->query_possessive()+" butt!\n");
         TP->command("blush");
         return 1;
        break;
        case 1:
         write("You accidentaly step on the warwolf's foot while trying to "+
         "mount him, and he snarls at you and kicks you.  Ouch!!\n");
         write("Perhaps its time to improve your ability to ride and handle warwolves.\n");
         say(QCTNAME(TP)+" accidentaly steps on the wolf's foot while "+
         "trying to mount it, and it snarls at "+HIM(TP)+" and kicks "+
         HIM(TP)+".\n");
         TP->command("blush");
         return 1;
        break;
        case 2:
         write("You try to mount the ferocious warwolf, but you accidentally "+
         "step over too far and fall down the other side.\n");
         write("Perhaps its time to improve some riding or handling skill.\n");
         say(QCTNAME(TP)+" tries to mount the wolf, but accidentally "+
         "steps over too far and falls down the other side.\n");
         TP->command("blush");
         return 1;
        break;
        }
        return 1;
    }
    // Add props to show we are on.
    add_prop(WOLF_O_OCCUPIED,this_player());
    TP->add_prop(WOLF_O_RIDING,TO);

    // Make the wolf getable
    remove_prop(OBJ_I_NO_GET);
    remove_prop(OBJ_I_NO_DROP);
    change_prop(CONT_I_WEIGHT,1);

    this_player()->add_prop(LIVE_S_EXTRA_SHORT," riding a "+short());
    TP->add_subloc(WOLF_SUBLOC,TO);
    // Add shadow
    sh = clone_object("/d/Kalad/common/wild/pass/goblin/guild/wolf_sh");
    sh->shadow_me(TP);
    sh->set_wolf(TO);

    write("You mount the "+short()+".\n");
    say(QCTNAME(TP)+" mounts the "+short()+".\n");

    TP->add_prop(ROOM_I_IS,1);
    TO->move_living("M",TP,1,1);
    TP->add_prop(ROOM_I_IS,0);
    set_no_show();

    // Make it examinable to others
    TP->add_item("warwolf","This is a strong and ferocious looking wolf. Bred by "+
   "the Riders of the Red Fang to be agile, strong and very efficient "+
   "killers. Only Riders of the Red Fang could be able to handle this "+
   "massive beast. Perhaps it is the fact that it's the size of a small "+
   "horse, or maybe because its fangs are half a foot long, but something "+
   "about this wolf makes you want to run and hide. "+QCTNAME(TP)+" is riding it."+
   "@@query_collar:"+file_name(TO)+"@@");
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
    set_this_player(ob);
    notify_fail("You are not riding it.\n");
    if (query_prop(WOLF_O_OCCUPIED)!= TP)
        return 0;

    remove_prop(WOLF_O_OCCUPIED);
    change_prop(OBJ_I_NO_GET,1);

    move_living("M",E(TP),1,1);

    change_prop(CONT_I_WEIGHT,10000);
    change_prop(OBJ_I_VOLUME,5000);

    unset_no_show();
    set_no_show_composite(0); 
    TP->remove_prop(LIVE_S_EXTRA_SHORT);

    TP->remove_prop(WOLF_O_RIDING);
    TP->remove_item("warwolf");
    TP->remove_subloc(WOLF_SUBLOC);
    
    TP->remove_shadow("/d/Kalad/common/wild/pass/goblin/guild/wolf_sh");

    return 1;
}

