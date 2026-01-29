/*
 * /d/Kalad/common/guilds/khiraa/lp/commands/common_soul
 * Purpose    : Command soul common to both parts of the guild
 * Located    : 
 * Created By : Sarr 14.Apr.97
 * Modified By: Toby 16.Sept.97 (Corected typo in cgrin)
 */


#pragma strict_types
inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h" // Kalad defs
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h" // Guild specific defs
#include <composite.h>

#define KHIRAA_CORPSE_HANDS_OFF "_khiraa_corpse_hands_off"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Khiraa"; }

public mapping
query_cmdlist()
{
    return ([
            ]);
}


float
compute_speed_to_round(object me, float round)
{
    float speed;
    int i = me->query_prop(LIVE_I_QUICKNESS);
    speed = 5.0 - (itof(i) / 50.0);
    speed = MAX(2.0,speed);
    return speed * round;
}

/* Guild master command tell */

int
isk(object ob)
{
    if(IS_DK(ob) || IS_LP(ob))
        return 1;
    return 0;
}

int
e_ckatell(string str)
{
    object *obs;
    int i;
    if(!IS_GUILD_MASTER(TP))
        return 0;
    obs = users();
    obs = filter(obs,isk);
    obs -= ({TP});
    for(i=0;i<sizeof(obs);i++)
    {
        tell_object(obs[i],TP->query_name()+" tells the Khiraa: "+
        str+"\n");
    }
    write("You told '"+str+"' to "+COMPOSITE_LIVE(obs)+".\n");
    return 1;
}


/****************COMMON EMOTES ********************************/


int
e_csoul(string str)
{
    object *obs;
    string tmp;
    NF("Soul whom?\n");
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        NF("Only one person at a time.\n");
        if(sizeof(obs) > 1)
            return 0;
        else
            tmp = HIS(obs[0]);
        actor("You gaze at",obs," steadily, searching "+
        tmp+" soul.");
        targetbb(" gazes at you steadily, seemingly searching your soul.",obs);
        all2actbb(" gazes at",obs," steadily, seemingly searching "+tmp+ 
        " soul.");
        return 1;
    }
    return 0;
}

int
e_cfurl(string str)
{
    object *obs;
    NF("Furl at who?\n");
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs))
        return 0;
    actor("You glance at",obs,", furling your brow.");
    targetbb(" glances in your direction, furling "+HIS(TP)+" brow.",obs);
    all2actbb(" glances at",obs,", furling "+HIS(TP)+" brow.");
    return 1;
}

int
e_camuse()
{
    write("A brief, eerie flicker of amusement crosses your face.\n");
    tell_room(E(TP),"You see an eerie flicker of amusement on "+
    QTNAME(TP)+"'s face.\n",TP);
    return 1;
}

int
e_cglint()
{
    write("Your eyes glint with the mysterious powers of the forbidden.\n");
    say(QCTNAME(TP)+"'s eyes glint with the mysterious powers of the "+
    "forbidden.\n");
    return 1;
}


int
e_cgreet(string str)
{
    object *obs;
    NF("Greet whom?\n");
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs) && str)
        return 0;
    if(sizeof(obs))
    {
        actor("You greet",obs," by bowing your head and intoning in a "+
        "hollow voice: Hail the Unnamable Horror!");
        targetbb(" greets you by bowing "+HIS(TP)+" head and intoning "+
        "in a hollow voice: Hail the Unnamable Horror!");
        all2actbb(" greets",obs," by bowing "+HIS(TP)+" head and "+
        "intoning in a hollow voice: Hail the Unnamable Horror!");
        return 1;
    }
    write("You greet everyone by bowing your head and intoning in a "+
    "hollow voice: Hail the Unnamable Horror!\n");
    allbb(" greets everyone by bowing "+HIS(TP)+" head and intoning in "+
    "a hollow voice: Hail the Unnamable Horror!");
    return 1;
}

int
e_cfare(string str)
{
    object *obs;
    NF("Farewell to whom?\n");
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs) && str)
        return 0;
    if(sizeof(obs))
    {
        actor("You bid",obs," farewell, intoning in a hollow voice"+
        ": Darkness eternal...");
        targetbb(" bids your farewell, intoning in a hollow voice"+ 
        ": Darkness eternal...",obs);
        all2actbb(" bids",obs," farewell, intoning in a hollow voice"+
        ": Darkness eternal...");
        return 1;
    }
    write("You bid everyone farewell, intoning in a hollow voice"+
    ": Darkness eternal...\n");
    allbb(" bids everyone farewell, intoning in a hollow voice"+
    ": Darkness eternal...");
    return 1;
}


int
e_cpraise()
{
    write("You praise all that is macabre and unholy, secure in "+
    "the ancient lore of the forbidden.\n");
    allbb(" praises all that is macabre and unholy, secure in the "+
    "ancient lore of the forbidden.");
    return 1;
}

int
e_cstroke(string str)
{
    object med;
    med = present("lich_medallion",TP);
    if(!objectp(med))
        med = present("death_knight_medallion",TP);
    NF("You don't have your medallion!\n");
    if(!objectp(med))
        return 0;
    write("You stroke your "+med->short()+" absentmindedly, deep in "+
    "thought.\n");
    allbb(" strokes "+HIS(TP)+" "+med->short()+" absentmindedly, "+
    "apparently deep in thought.");
    return 1;
}

int
e_crad()
{
    int i;
    object *obs;
    write("Waves of bone-numbing coldness flow from your body, sucking "+
    "the warmth out of all that is around you.\n");
    tell_room(E(TP),"Waves of bone-numbing coldness flow from "+QTNAME(TP)+
    "'s body, sucking the warmth out of all that is around "+HIM(TP)+".\n",TP);

    obs = FILTER_LIVE(all_inventory(E(TP)));
    for(i=0;i<sizeof(obs);i++)
    {
        if(!obs[i]->query_prop(LIVE_I_UNDEAD))
            obs[i]->command("shiver");
    }
    return 1;
}

int
e_cturn(string str)
{
    object *obs,ob;
    NF("Turn to whom?\n");
    if(!str)
        return 0;
    obs = parse_this(str,"[the] %l");
    if(!sizeof(obs))
        return 0;
    ob = obs[0];
    actor("You slowly turn your head and look at",obs,".");
    targetbb(" slowly turns "+HIS(TP)+" head and "+
    "looks at you.",obs);
    all2actbb(" slowly turns "+HIS(TP)+" head and "+
    "looks at",obs,".");
    return 1;
}


int
e_crage(string str)
{
    object *targets;
    NF("Rage at whom?\n"); 
    targets = parse_this(str,"[at] [the] %l");
    if(!sizeof(targets) && str)
        return 0;
    if(sizeof(targets))
    {
        actor("You give",targets," a burning look of utter rage from "+
        "the depths of your accursed soul.");
        all2actbb(" gives",targets," a burning look of utter rage from "+
        "the depths of "+HIS(TP)+" accursed soul.");
        targetbb(" gives you a burning look of utter rage from the "+
        "depths of "+HIS(TP)+" accursed soul.",targets);
        return 1;
    }
    write("Your accursed soul burns with inhuman rage.\n");
    allbb("'s accursed soul burns with inhuman rage.\n");
    return 1;
}




int
e_cglow()
{
    write("Your eyes begin to glow as you feel the unholy powers of "+
    "the forbidden course through you.\n");
    allbb("'s eyes begin to glow as "+HE(TP)+" feels the "+
    "unholy powers of the forbidden course through "+HIM(TP)+".");
    return 1;
}

    
int
e_cgrin(string str)
{
    object *obs;
    string *advs,adv;
    NF("Grin [how] at whom?\n");
    advs = parse_adverb_with_space(str,"evilly",0);
    adv = advs[1];
    str = advs[0];
    obs = parse_this(str,"[at] [the] %l");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        actor("You grin"+adv+" at",obs,", an unstable glint "+
        "in your eyes.");
        all2actbb(" grins"+adv+" at",obs,", an unstable glint "+
        "in "+HIS(TP)+" eyes.");
        targetbb(" grins"+adv+" at you, an unstable glint "+
        "in "+HIS(TP)+" eyes.",obs);
        return 1;
    }
    write("You grin"+adv+", an unstable glint in your eyes.\n");
    allbb(" grins"+adv+", an unstable glint in "+
    HIS(TP)+" eyes.");
    return 1;
}

int
e_cchant()
{

    all(" eerily chants strange words that seem to echo through the "+
    "room.");
    write("You eerily chant unholy praises of the forbidden that seem to echo "+
    "through the room.\n");
    return 1;
}


int
e_csmile(string str)
{
    object *obs;
    string *advs,adv;
    NF("Smile [how] at whom?\n");
    advs = parse_adverb_with_space(str,"evilly",0);
    adv = advs[1];
    str = advs[0];
    obs = parse_this(str,"[at] [the] %l");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        actor("You smile"+adv+" at",obs," with the coldness of the grave "+
        "radiating from your body.");
        all2actbb(" smiles"+adv+" at",obs," with the coldness of the grave "+
        "radiating from "+HIS(TP)+" body.");
        targetbb(" smiles"+adv+" at you with the coldness of the grave "+
        "radiating from "+HIS(TP)+" body.",obs);
        return 1;
    }
    write("You smile"+adv+" with the coldness of the grave radiating from "+
    "your body.\n");
    allbb(" smiles"+adv+" with the coldness of the grave "+
    "radiating from "+HIS(TP)+" body.");
    return 1;
}

int
e_cmemory()
{
    write("Your eyes narrow and attain a distant look as you think on "+
    "some long forgotten memory of that other life.\n");
    allbb("'s eyes narrow and attain a distant look as "+HE(TP)+" thinks "+
    "on some long forgotten memory of another life.\n");
    return 1;
}

int
e_cfrustrate()
{
    write("You claps your hands to the sides of your head and "+
    "scream in frustration.\n");
    allbb(" clasps "+HIS(TP)+" hands to the sides of "+HIS(TP)+" head "+
    "and screams in frustration.\n");
    return 1;
}


int
e_cglare(string str)
{
    object *obs;
    string *advs,adv;
    NF("Glare [how] at whom?\n");
    advs = parse_adverb_with_space(str,"angrily",0);
    adv = advs[1];
    str = advs[0];
    obs = parse_this(str,"[at] [the] %l");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        actor("You glare"+adv+" at",obs," with utter hatred burning "+
        "in your damned soul.");
        all2actbb(" glares"+adv+" at",obs," with utter hatred burning "+
        "in "+HIS(TP)+" damned soul.");
        targetbb(" glares"+adv+" at you with utter hatred burning "+
        "in "+HIS(TP)+" damned soul.",obs);
        return 1;
    }
    write("You glare"+adv+" with utter hatred burning in your "+
    "damned soul.\n");
    allbb(" glares"+adv+" with utter hatred burning in "+
    HIS(TP)+" damned soul.");
    return 1;
}


int
e_cchuckle(string str)
{
    string *advs,adv;
    advs = parse_adverb_with_space(str,"softly",0);
    adv = advs[1];
    str = advs[0];
    write("You chuckle"+adv+", your terrible eyes sparkling with "+
    "unholy amusement.\n");
    all(" chuckles"+adv+", "+HIS(TP)+" terrible eyes "+
    "sparkling with unholy amusement.");
    return 1;
}


int
e_chiss(string str)
{
    object *obs;
    string adv,*advs;
    advs = parse_adverb_with_space(str,"dangerously",0);
    adv = advs[1];
    str = advs[0];
    obs = parse_this(str,"[at] / [toward] [the] %l");
    NF("Hiss [how] at whom?\n");
    if(str && !sizeof(obs))
        return 0;
    if(sizeof(obs))
    {
        actor("You snap your head around and hiss"+adv+" at",obs,".");
        all2actbb(" snaps "+HIS(TP)+" head around and hisses"+adv+" at",
        obs,".");
        targetbb(" snaps "+HIS(TP)+" head around at you and hisses"+
        adv+".",obs);
        return 1;
    }
    write("Eye's blazing red, you hiss"+adv+".\n");
    allbb("'s eyes blaze red as "+HE(TP)+" hisses"+adv+".\n");
    return 1;
}


int
e_cwail()
{
    int i;
    object *obs = ({});
    write("You let out an eerie wail that seems to echo around "+
    "the area.\n");
    all(" lets out an eerie wail that seems to echo around "+
    "the area.");
    obs = FILTER_OTHER_LIVE(all_inventory(E(TP)));
    for(i=0;i<sizeof(obs);i++)
    {
        if(!obs[i]->query_prop(LIVE_I_UNDEAD))
        {
            tell_object(obs[i],"You shudder slighly at its horrible sound.\n");
            tell_room(E(obs[i]),QCTNAME(obs[i])+" shudders slightly at "+
            "its horrible sound.\n",obs[i]);
        }
        else
            tell_object(obs[i],"You find the sound quite pleasing.\n");
    }
    return 1;
}

        
int
e_cscream(string str)
{
    object *targets;
    targets = parse_this(str,"[at] / [toward] [the] %l");
    NF("Scream at whom?\n");
    if(!sizeof(targets) && str)
        return 0;
    if(sizeof(targets))
    {
        if(sizeof(targets) > 1)
            actor("You let out a horrible shriek of fury at",targets,
            ". They take a few steps back.");
        else
           actor("You let out a horrible shriek of fury at",targets,
           ". "+C(HE(targets[0]))+" takes a few steps back.");
        all2act(" lets out a horrible shriek of fury at",targets,".");
        targetbb(" lets out a horrible shriek of fury at you. You "+
        "take a few steps back.",targets);
        return 1;
    }
    write("You let out a horrible shrieking scream of fury!\n");
    all(" lets out a horrible shrieking scream of fury!");
    return 1;
}


/**************** COMMON COMMMANDS ****************************/

/* Torment ability */

int
c_crot(string str)
{
    mixed leftovers;
    int i,j;
    object lft,*corpses,corpse;
    setuid();
    seteuid(getuid());
    corpses = FIND_STR_IN_OBJECT(str, E(TP) );
    NF("Rot what corpse?\n");
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];
    if(!corpse->id("corpse") || living(corpse) )
        return 0;
    leftovers = corpse->query_leftover();
    for(i = 0; i <sizeof(leftovers); i++)
    {
        for(j = 0; j < leftovers[i][2]; j++)
        {
            lft = clone_object(leftovers[i][0]);
            lft->leftover_init(leftovers[i][1],
                corpse->query_prop(CORPSE_S_RACE));
            lft->move(E(TP),0);
        }
    }
    corpses = all_inventory(corpse);
    for(i = 0; i < sizeof(corpses);i++)
    {
        if(corpses[i]->move(E(TP)) )
            corpses[i]->remove_object();
    }
    write("You kneel down and touch the "+corpse->short()+".\n");
    say(QCTNAME(TP)+" kneels down and touches the "+corpse->short()+".\n");
    tell_room(E(corpse),"The "+corpse->short()+" slowly decays away into "+
    "a puddle of goo, then turns to dust and blows away.\n");
    corpse->remove_object();
    return 1;
}



/* Cut hands/fingers/ off corpse */

int
c_ccut(string str)
{
    int i;
    string wht,crps;
    object corpse,*corpses,item;
    NF("Cut what off what?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s off %s",wht,crps) != 2)
        return 0;
    if(member_array(wht,({"hands","fingers"})) == -1)
        return 0;
    corpses = FIND_STR_IN_OBJECT(crps,E(TP));
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];
    if(!objectp(corpse) || !corpse->id("corpse") || living(corpse))
        return 0;
    NF("That corpse already has its hands cut off.\n");
    if(corpse->query_prop(KHIRAA_CORPSE_HANDS_OFF))
        return 0;
    setuid();
    seteuid(getuid());
    if(wht == "hands")
    {
        i=2;
        while(i--)
        {
            item = clone_object(KHIRAA_DIR(temple/obj/bloody_hand));
            item->set_race(corpse->query_race());
            item->move(TP);
        }
    }
    if(wht == "fingers")
    {
        i = 10;
        while(i--)
        {
            item = clone_object(KHIRAA_DIR(temple/obj/bloody_finger));
            item->move(TP);
        }
    }
    write("You brutally cut off the "+wht+" of the "+corpse->short()+".\n");
    say(QCTNAME(TP)+" brutally cuts off the "+wht+" of the "+
    corpse->short()+".\n");
    corpse->add_prop(KHIRAA_CORPSE_HANDS_OFF,1);
    corpse->set_short("handless "+corpse->short());
    return 1;
}



/* Hang up a corpse with a hook or rope */

int
c_crucify(string str)
{
    object *corpses, corpse,crux;
    NF("Crucify what corpse?\n");
    if(!str)
        return 0;
    corpses = FIND_STR_IN_OBJECT(str,E(TP));
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];
    NF("Thats not a corpse.\n");
    if(!corpse->id("corpse") || living(corpse))
        return 0;
    NF("You don't have the crucifix poles.\n");
    if(!present("_crucifix_poles_",TP))
        return 0;
    NF("You do not have the mana to cast the magic words.\n");
    if(TP->query_mana() < 20)
        return 0;
    TP->add_mana(-20);
    write("You set up the crucifix on the ground here, then nail "+
    "up the "+corpse->short()+".\n");
    write("You chant magical words, and the corpse bursts into flames!\n");
    say(QCTNAME(TP)+" sets up a crucifix on the ground here, then nails "+
    "up the "+corpse->short()+" on it.\n");
    say(QCTNAME(TP)+" chants magical words, and the corpse bursts into "+
    "flames!\n");
    setuid();
    seteuid(getuid());
    crux = clone_object(KHIRAA_DIR(temple/obj/crucifix));
    crux->set_real_name(C(corpse->query_real_name()));
    crux->set_race_name(corpse->query_race_name());
    crux->set_corpse_short(corpse->query_nonmet_name());
    crux->add_prop(OBJ_I_WEIGHT,corpse->query_prop(CONT_I_WEIGHT));
    crux->add_prop(OBJ_I_VOLUME,corpse->query_prop(CONT_I_VOLUME));
    crux->move(E(TP));
    corpse->remove_object();
    present("_crucifix_poles_",TP)->remove_object();
    return 1;
}

int
c_chang(string str)
{
    string loc,stool,from_type,scorpses;
    object *inv;
    object *corpses,corpse,hanged,tool;
    int i,index;
    mixed *its;
    NF("Hang what corpse up on what with what?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s up on %s with %s",scorpses,loc,stool) != 3)
        return 0;
 
    corpses = FIND_STR_IN_OBJECT(scorpses,E(TP));
 
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];

    if(!objectp(corpse))
        return 0;

    tool = FIND_STR_IN_OBJECT(stool,TP)[0];

    if(!objectp(tool))
        return 0;
    if(!corpse->id("corpse") || living(corpse))
        return 0;
    if(!stringp(loc))
        return 0;
    inv = all_inventory(corpse);
    NF("You must empty the "+corpse->short()+" first.\n");
    if(sizeof(inv))
        return 0;
    NF("That corpse is already hanged.\n");
    if(MASTER_OB(corpse) == DK_DIR(obj/corpse_hang))
        return 0;
    NF("The location "+loc+" is not a valid choice.\n");
    if(member_array(loc,({"tree","wall","ceiling"})) == -1)
        return 0;
    NF("There is no "+loc+" in the area!\n");
    its = E(TP)->query_item();
    for(i=0;i<sizeof(its);i++)
    {
        index = member_array(loc,its[i][0]);
        if(index == -1)
            index = member_array(loc+"s",its[i][0]);
        if(index != -1)
        {
            loc = its[i][0][index];
            break;
        }
    }
    if(index == -1)
        return 0;
    if(loc == "walls")
        loc = "wall";
    if(loc == "tree" || loc == "trees")
        loc = "on a nearby tree";
    else
        loc = "in the "+loc;
    NF("You can't use that to hang the "+corpse->short()+".\n");
    if(tool->id("hook"))
        stool = "hook";
    if(tool->id("rope"))
        stool = "rope";
    if(!stringp(stool))
        return 0;
    NF("You cannot use a rope on a wall. Use a hook instead.\n");
    if(stool == "rope" && loc == "in the wall")
        return 0;
    from_type = "a "+stool+" "+loc;
    setuid();
    seteuid(getuid());
    hanged = clone_object(DK_DIR(obj/corpse_hang));
    hanged->set_from_type(from_type);
    hanged->set_real_name(C(corpse->query_real_name()));
    hanged->set_race_name(corpse->query_race_name());
    hanged->set_corpse_short(corpse->query_nonmet_name());
    hanged->add_prop(OBJ_I_WEIGHT,corpse->query_prop(CONT_I_WEIGHT));
    hanged->add_prop(OBJ_I_VOLUME,corpse->query_prop(CONT_I_VOLUME));
    hanged->move(E(TP));
    TP->catch_msg("You hang up the "+corpse->short()+" "+loc+" with "+
    "a "+stool+".\n");
    say(QCTNAME(TP)+" hangs up the "+corpse->short()+" "+loc+" with "+
    "a "+stool+".\n");
    write("Then you paint the symbol of the Khiraa on its torso with "+
    "its blood.\n");
    say(QCTNAME(TP)+" writes something on it.\n");
    corpse->remove_object();
    tool->remove_object();
    return 1;
}

/* Discover the killer's name */
  
int
c_ccorpse(string str)
{
    int i;
    object corpse,*obs;
    string str2;
    string kname;
    NF("Corpse what?\n");
    if(!str)
        return 0;
    obs = FIND_STR_IN_OBJECT(str,E(TP));
    if(!sizeof(obs))
        return 0;
    corpse = obs[0];
    if(!objectp(corpse))
        return 0;
    if(!corpse->id("corpse") || living(corpse))
        return 0;
    if(TP->query_armour(A_R_HAND))
        str2 = "armoured";
    else
        str2 = "skeletal";
    if(!sizeof(corpse->query_prop(CORPSE_AS_KILLER)))
    {
        write("You feel powers blocking you from revealing its killer.\n");
        return 1;
    }
    kname = corpse->query_prop(CORPSE_AS_KILLER)[0];
    write("You kneel down and place your "+str2+" hand on the "+corpse->short()+
    ".\n");
    say(QCTNAME(TP)+" kneels down and places "+HIS(TP)+" "+str2+" hand on "+
    "the "+corpse->short()+".\n");
    tell_room(E(TP),"The "+corpse->short()+" suddenly sits up and "+
    "shrieks: "+C(kname)+"!\n");
    obs = FILTER_OTHER_LIVE(all_inventory(E(TP)));
    for(i=0;i<sizeof(obs);i++)
    {
        if(!obs[i]->query_prop(LIVE_I_UNDEAD))
        {
            tell_object(obs[i],"You shudder and put your hands to your "+
            "ears to stop from hearing to that horrible scream.\n");
            tell_room(E(obs[i]),QCTNAME(obs[i])+" shudders and puts "+
            HIS(obs[i])+" hands to "+HIS(obs[i])+" ears to stop from "+
            "hearing that horrible scream.\n",obs[i]);
        }
    }
    return 1;
} 

/* The Undead Speech */

void
do_say(object ob, string str, object me, object tar)
{
    if(!objectp(tar))
    {
        if(IS_LP(ob) || IS_DK(ob))
            tell_object(ob,me->query_The_name(ob)+" hisses in the secret "+
            "Khiraa tongue: "+str+"\n");
        else
            tell_object(ob,me->query_The_name(ob)+" makes a series of "+
            "strange hisses and clicks.\n");
        return;
    }
    if(ob == tar)
    {
        tell_object(ob,me->query_The_name(ob)+" hisses in the secret "+
        "Khiraa tongue to you: "+str+"\n");
        return;
    }
    if(!IS_DK(ob) && !IS_LP(ob))
    {
        tell_object(ob,me->query_The_name(ob)+" makes a series of "+
        "strane hisses and clicks at "+tar->query_the_name(ob)+".\n");
        return;
    }
    tell_object(ob,me->query_The_name(ob)+" hisses in the secret "+
    "Khiraa tongue to "+tar->query_the_name(ob)+": "+str+"\n");
}

int
c_lksay(string str)
{
    string st2,st3;
    object *zzs,tar;
    NF("Say what in the secret Khira tongue?\n");
    if(!str)
        return 0;
    if(sscanf(str,"to %s %s",st2,st3) == 2)
    {
        NF("Speak in the Khiraa tongue to who?\n");
        zzs = parse_this(st2,"[the] %l");
        if(!sizeof(zzs))
            return 0;
        tar = zzs[0];
        NF("That one does not know this secret tongue.\n");
        if(!IS_DK(tar) && !IS_LP(tar))
            return 0;
    }
    if(!objectp(tar))
        st3 = str;
    if(objectp(tar))
        TP->catch_msg("You hiss in the secret Khiraa tongue to "+
        QTNAME(tar)+": "+st3+"\n");
    else
        write("You hiss in the secret Khiraa tongue: "+st3+"\n");
    filter(FILTER_OTHER_LIVE(all_inventory(E(TP))),&do_say(,st3,TP,tar));
    return 1;
}


/* list guild memembers on */

public string
q_title(object ob, int wiz)
{
    string str;
    str = "";
    if ( IS_DK(ob) )
    {
        if(ob->query_circle() == 3)
            str += "Grand Master "+ob->query_name()+" of the Khiraa";
        else
            str += ob->query_name()+" the "+ob->query_guild_title_occ();
        return str;
    }
    if ( IS_LP(ob) )
    {
        if(ob->query_wiz_level())
            str += C(ob->query_title())+" ("+ob->query_name()+")";
        else
        {
            if(stringp(ob->query_guild_name_race()))
                str += C("The "+ob->query_lich_name()+", "+
                ob->query_guild_title_occ())+" ("+ob->query_name()+")";
            else
                str += C("The "+ob->query_guild_title_occ())+
                " ("+ob->query_name()+")";
        }
        return str;
    }
    return 0;
}

public int
c_wkhiraa()
{
    int i = 0;
    say(QCTNAME(TP)+" looks into the sky with blazing eyes.\n");
    write("You look towards Raumdor with your eyes blazing, and call upon "+
    "the Nameless Horror to tell you which of his servants are currently "+ 
    "walking the realms:\n\n"+
        implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
            "\n") + "\n\n");
    return 1;
}
