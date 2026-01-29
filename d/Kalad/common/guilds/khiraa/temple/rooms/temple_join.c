// 	modified: Toby 96-07-18 (fixed typos)
//                Sarr 26.Mar.98 (updated for new code)
// Valen, Jul 2004, fixed runtime error

#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include <wa_types.h>
#pragma strict_types
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("A foul chamber");
    
    set_long("\n   You now find yourself in a grim looking chamber. The "+
    "walls here are all made of black stone, and there are numerous markings "+
    "on them. The ceiling is higher up here, and you can see what "+
    "appears to be a floating orb near the very top. It is glowing "+
    "a bright purple, lighting up the entire room. The floor is "+
    "made of black polished marble, and there is a large red grim "+
    "skull painted on it.\n"+
    "   In the center of the red grim skull is a large, black altar. "+
    "The altar itself is made of stone, and has many interesting "+
    "markings on it. Next to the altar, there is a black wooden "+
    "stand with a book on it. In the far corner, you see an eerie "+
    "wooden coffin placed up against the wall. The air is filled with "+
    "death and decay, and a chill that sinks right down to your bones. "+
    "You feel that there is great magic at work here.\n\n");
   
    add_item("walls","The walls are made of cold black stone, and are "+
    "smooth to the touch. Upon them, many mysterious red runes are "+
    "carved in.\n");
    add_item("floor","The floor is made of polished black marble, and "+
    "painted on it is a large, red grim skull, the center of which "+
    "sits a large black altar.\n");
    add_item("ceiling","The ceiling is high here, and is slightly "+
    "vaulted. At the very top, right over the large black altar, "+
    "you see a floating orb.\n");
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item(({"skull","red skull","red grim skull","grim skull"}),
    "The large red skull seems to be a painting. It looks ghastly. "+
    "In the center of its mouth, the large black altar sits.\n");
    add_item(({"orb","floating orb"}),"The floating orb radiates "+
    "a purple glow that illuminates the room somewhat. It hovers "+
    "over the large black altar.\n");
    add_item(({"large altar","large black altar","black altar","altar"}),
    "The large black altar is made of solid black marble. On it, you "+
    "see many red runes and symbols. The surface is perfectly smooth, "+
    "but you can see what appears to be dried blood on it.\n");

    INSIDE;
    clone_object(KHIRAA+"temple/doors/coffin_out")->move(TO);
    clone_object(KHIRAA+"temple/obj/join_book")->move(TO);

    add_exit(KHIRAA+"temple/rooms/t8","west",0,-1);
}

void
welcome(object me)
{
    me->remove_prop(KHIRAA_JOIN_INITIATE);
    me->remove_prop(LIVE_I_SEE_DARK);
}


int
init_join(object joiner, string OccShadow)
{
    object cerdag;
    object occ_sh;
    string adjs;

    cerdag = TP->query_weapon(W_RIGHT);

    if(sizeof(joiner->query_prop(KHIRAA_JOIN_ADJS)))
        adjs = joiner->query_prop(KHIRAA_JOIN_ADJS)[0]+","+
               joiner->query_prop(KHIRAA_JOIN_ADJS)[1];

    write("You plunge your "+cerdag->short()+" into the marked circle "+
    "on the bare chest of "+joiner->query_name()+"!\n");

    tell_room(TO,QCTNAME(TP)+" plunges "+HIS(TP)+" "+cerdag->short()+
    " into the marked circle on the bare chest of "+joiner->query_name()+
    "!\n",({TP,joiner}));

    tell_object(joiner,TP->query_name()+" plunges "+HIS(TP)+" "+
    cerdag->short()+" into the marked circle on your bare chest!\n");
    
    occ_sh = clone_object(OccShadow);
    if(occ_sh->join_khiraa(joiner,adjs,TP) != 1)
        return 0;

    // Kill player
    joiner->set_hp(0);
    // joiner->heal_hp(-10000);
    joiner->query_hp();
    // joiner->do_die(TO);

    // Return to coffin after death
    set_alarm(1.5,0.0,"return_me",joiner);

    return 1;
}

int
join_khiraa(object ini, object joiner, int sec)
{
    string nam;
    nam = joiner->query_name();
    set_this_player(ini);

    if(!joiner->query_prop(KHIRAA_CIRCLE_PERMISSION))
    {
        write(nam+" has not been granted permission to join by the "+
        "circle.\n");
        return 0;
    }

    if(stringp(joiner->query_guild_name_occ()) )
    {
        write(nam+" already has an occupational guild!\n");
        return 0;
    }

    if(stringp(joiner->query_guild_name_lay()) )
    {
        write(nam+" has a layman guild already!\n");    
        return 0;
    }
    
    if(joiner->query_alignment() > -400)
    {
        write(nam+" is not dark of heart enough to join us.\n");
        return 0;
    }
    
    if(!objectp(TP->query_weapon(W_RIGHT)) || 
MASTER_OB(TP->query_weapon(W_RIGHT)) != KHIRAA+"temple/obj/cer_dagger")
    {
        write("You do not have the initiation dagger wielded in your right "+
        "hand.\n");
        return 0;
    }
    if(sec == 0)
        return init_join(joiner,LP_OCC_SHADOW);
    return init_join(joiner,DK_OCC_SHADOW);
}

int
do_join(string str)
{
    string str2,str3;
    object joiner;

    NF("You are not allowed to initiate people!\n");
    if( !IS_LP(TP) && !IS_DK(TP) )
        return 0;

    NF("Initiate whom to the order of the what?\n");
    if(!str)
        return 0;

    if(sscanf(str,"%s to the order of the %s",str2,str3) != 2)
        return 0;

    joiner = present(str2,TO);

    NF("There is no one here by that name.\n");
    if(!objectp(joiner))
        return 0;

    NF("Initiation failed.\n");

    if(str3 == "knights")
        return join_khiraa(TP,joiner,1);
    if(str3 == "lichs")
        return join_khiraa(TP,joiner,0);

    NF("Initiate whom to the order of the what?\n");
    return 0;
}

void
return_me(object joiner)
{
    clone_object(KHIRAA+"temple/obj/death_flag")->move(joiner);
}

int
do_leave(string str)
{
    mapping temp;
    NF("Betray the what?\n");

    if(!str || str != "the khiraa")
        return 0;

    NF("You are not a member of the Khiraa!\n");
    if(!IS_DK(TP) && !IS_LP(TP))
        return 0;

    write("\nYou decided to betray the Khiraa!\n\n");
    say(QCTNAME(TP)+" betrays the Khiraa!\n");

    write("You are suddenly consumed in a plume of black magick that "+
    "sprouts from the ground!\n");
    say(QCTNAME(TP)+" is suddenly consumed in a plume of black magick "+
    "that sprouts from the ground!\n");

    if(present("_dk_scab_",TP))
        present("_dk_scab_",TP)->remove_object();
    if(present("death_knight_medallion",TP))
        present("death_knight_medallion",TP)->remove_object();
    if(present("lich_medallion",TP))
        present("lich_medallion",TP)->remove_object();

    NF("Something has gone wrong, mail guildmaster.\n");
    if(!TP->remove_guild_occ())
        return 0;
    if(!TP->remove_guild_lay())
        return 0;

    KHIRAA_SERVER->remove_member(TP->query_real_name());

    write_file(BETRAY_LOG,ctime(time())+": "+TP->query_real_name()+
    " betrayed the khiraa.\n");

    tell_room(TO,"Screams from the Netherworld sing in sorrow as a "+
    "once devout servant of Him has betrayed them for the foul "+
    "existence of life!\n");

    write("You burn to death.\n");

    TP->command("scream");
    TP->set_hp(0);
    TP->query_hp();
    TP->do_die(TO);    
    return 1;
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him. The portal of Death awaits.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}

int
do_step1(string str)
{
    object tar;
    if(IS_DK(TP) || IS_LP(TP))
    {
        NF("That person is not present.\n");
        tar = present(str,TO);
        if(!objectp(tar))
            return 0;
        write("You place "+tar->query_name()+" on the altar, and begin "+
        "to chant to the Nameless One, and all His servants.\n");
        tell_room(TO,QCTNAME(TP)+" places "+tar->query_name()+" on "+
        "the altar, and begins to chant to the Nameless One, and all His "+
        "servants.\n",({TP,tar}));
        tell_object(tar,TP->query_name()+" places you on the altar and "+
        "begins to chant to the Nameless One, and all His servants.\n");
        return 1;
    }
    return 0;
}

int
do_step2()
{
    if(IS_DK(TP) || IS_LP(TP))
    {
        write("You chant: By Gol Dek, by Shaadok Y'Sulgash, by He "+
        "whose name is unspeakable, I praise thee, oh Lords of Darkness "+
        "and Death, that you may deliver upon us a new servant with "+
        "your unholy blessings.....\n");
        say(QCTNAME(TP)+" chants: By Gol Dek, by Shaadok Y'Sulgash, by "+
        "He whose name is unspeakable, I praise thee, oh Lords of "+
        "Darkness and Death, that you may deliver upon us a new servant "+
        "with your unholy blessings....\n");
        return 1;
    }
    return 0;
}


int
do_step3(string str)
{
    object tar;
    if(IS_DK(TP) || IS_LP(TP))
    {
        tar = present(str,TO);
        NF("That person is not here.\n");
        if(!objectp(tar))
            return 0;
        NF("You do not have the ceremonial bowl of blood!\n");
        if(!present("_join_bowl_",TP))
            return 0;
        write("You dip your hands into the ornate golden bowl of "+
        "blood, then begin to "+
        "mark elaborate pentagrams, runes and skulls on the "+
        "bare chest of "+tar->query_name()+".\n");
        tell_room(TO,QCTNAME(TP)+" dips "+HIS(TP)+" hands into the "+
        "ornate golden bowl of blood,"+
        " then begins to mark elaborate pentagrams, runes and "+
        "skulls on the bare chest of "+tar->query_name()+".\n",({TP,tar}));
        tell_object(tar,TP->query_name()+" dips "+HIS(TP)+" hands into "+
        "a ornate golden bowl of blood, then begins to mark elaborate pentagrams, runes "+
        "and skulls on your bare chest.\n");
        return 1;
    }
    return 0;
}

int
do_select(string str)
{
    string adj1,adj2,padj1,padj2;
    string *my_own;
    int index;

    if(!str || intp(str))
    {
        NF("Select what ?\n");
        return 0;
    }

    if(str == "clear")
    {
        TP->remove_prop(KHIRAA_JOIN_ADJS);
        write("Cleared.\n");
        return 1;
    }
    NF("You must enter two adjectives in the form of:\n"+
       "select (adjective 1) and (adjective 2). They must be from the "+
       "list, or one of your current ones.\n");
    if(sscanf(str,"%s and %s",adj1,adj2) != 2)
        return 0;
    my_own = TP->query_adj(1);
    if( (index = member_array(adj1,my_own)) != -1)
        padj1 = my_own[index];
    if( (index = member_array(adj2,my_own)) != -1)
        padj2 = my_own[index];
    /* Yes, you could select both of your own, but no good to do so */
    if(  (index = member_array(adj1,KHIRAA_ADJ_LIST)) != -1)
        padj1 = KHIRAA_ADJ_LIST[index];
    if(  (index = member_array(adj2,KHIRAA_ADJ_LIST)) != -1)
        padj2 = KHIRAA_ADJ_LIST[index];
    NF("You did not select one from the list or from your own current "+
    "adjectives.\n");
    if(!stringp(padj1))
        return 0;
    if(!stringp(padj2))
        return 0;
    NF("They cannot be the same for both!\n");
    if(padj1 == padj2)
        return 0;
    TP->add_prop(KHIRAA_JOIN_ADJS,({padj1,padj2}));
    write("Selected: "+padj1+" and "+padj2+"\n");
    write("When you join, they will be taken into effect.\n");
    return 1;
}


int
do_list(string str)
{
    NF("List what?\n");
    if(str != "adjectives")
        return 0;
    TP->more(read_file(KHIRAA+"doc/alt_adjs"),0);
    return 1;
}


void
init()
{
    ::init();
    add_action(do_join,"initiate");
    add_action(do_leave,"betra");
    add_action(do_list,"list");
    add_action(do_select,"select");

    add_action(do_step1,"step1");
    add_action(do_step2,"step2");
    add_action(do_step3,"step3");

    if(TP->query_prop(KHIRAA_JOIN_INITIATE))
        set_alarm(2.0,0.0,&welcome(TP));
}

