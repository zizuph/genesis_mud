#include "/d/Ansalon/common/defs.h";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <cmdparse.h>

inherit "/std/weapon";
inherit "/lib/commands";

#define SUBLOC "pirate_hook_subloc"

create_weapon()
{
    set_name("hook");
    set_adj("steel");
    set_short("steel hook");
    set_long("This is a large hook that has been made out of steel. "+
             "A small handle has been attached to the end of it, making "+
             "it possible for people to hold, and perhaps use it as a "+
             "weapon. Some words are written on the handle.\n");
    set_default_weapon(35,35,W_KNIFE,W_IMPALE,W_RIGHT);
    set_likely_dull(0);
    set_wf(TO);
    add_prop(OBJ_I_VOLUME, 360);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_M_NO_SELL, 1);


    add_item(({"words", "word"}),"The words read:\n"+
                                "'hinform'          - Inform people about your hook.\n"+
                                "'hpick'            - Pick your nose with your hook.\n"+
                                "'hscrape' <target> - Make an irritating noise with your hook.\n"+
                                "'hsharpen'         - Sharpen your hook.\n"+
                                "'hshow' <target>   - Scare <target> with you hook.\n");


}

mixed
wield(object what)
{
    if (TP->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
        write("You grasp the " + short() + " with your right hand.\n");
        TP->add_subloc(SUBLOC, TO);
        return 1;
    }
    return "You can't get a decent grasp around the "+short()+", so you let go of it.\n";
}

mixed
unwield(object what)
{
    if (TP->query_guild_name_lay() == "Pirate of the Bloodsea")
      TP->remove_subloc(SUBLOC);
    return 0;
}

string
show_subloc(string subloc, object wielder, object for_obj)
{
    string str;

    if (wielder->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "Your right hand has been replaced with a "+short()+".\n";

    if (for_obj == wielder)
        str = "Your right hand ";
    else
        str = capitalize(wielder->query_possessive()) + " right hand ";

    return str + "has been replaced with a "+short()+".\n";
}

int
emote_hsharpen()
{
    write("You pull out a small stone from your pocket, and begin to "+
          "sharpen the "+short()+".\n");
    TP->tell_watcher(QCTNAME(TP)+ " pulls out a small stone "+
                     "from "+HIS(TP)+ " pocket and begins to "+
                     "sharpen "+HIS(TP)+ " "+short()+".\n");
    return 1;
}

int
emote_hinform()
{
    write("You carefully inform everyone in the room, that you don't "+
          "want your "+short()+" to be covered with blood...again.\n");
    TP->tell_watcher(QCTNAME(TP)+ " carefully informs you "+
                     "that "+HE(TP)+ " doesn't want "+HIS(TP)+
                     " "+short()+" to be covered with blood...again.\n");
    return 1;
}

int
emote_hshow(string str)
{
    object *ob;
    object obj;
    int diff;

    if(!strlen(str))
    {
	      notify_fail("Hshow your hook to whom?\n");
	      return 0;
    }

    ob = PARSE_THIS(str, "[to] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Hshow your hook to whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You menacingly show your "+short()+ " to", ob, ".");
    target(" menacingly shows you "+HIS(TP)+" "+short()+".", ob);
    all2act(" menacingly shows "+HIS(TP)+ " "+short()+ " to",ob,".");
  
    diff = TP->query_stat(SS_DIS) - obj->query_stat(SS_DIS);
     
    switch(diff)
    {
	case 100..300:
            actor("You laugh as", ob, " collapses on the ground shaking and whimpering!");
            target(" laughs as you collaps on the ground shaking and whimpering!", ob);
            all2act(" laughs as",ob," collapses on the ground shaking and whimpering!");
	break;

	case 50..99:
            actor("You grin as", ob, " squeals with anguish and fear!");
            target(" grins as you squeal with anguish and fear!", ob);
            all2act(" grins as",ob," squeals with anguish and fear!");
	break;

	case 25..49:
            actor("You chuckle slightly as", ob, " looks visibly disturbed!");
            target(" chuckles slightly as you look visibly disturbed!", ob);
            all2act(" chuckles slightly as",ob," looks visibly disturbed!");
	break;

	case 10..24:
            actor("You smile as", ob, " flinches slightly and adjusts "+HIS(obj)+" stance.");
            target(" smiles as you flinch slightly and adjust your stance.", ob);
            all2act(" smiles as",ob," flinches slightly and adjusts "+HIS(obj)+" stance.");
	break;

	case -24..9:
            actor("You sigh as", ob, " appears to be unphased by the provocation.");
            target(" sighs as you appear to be unphased by the provocation.", ob);
            all2act(" sighs as",ob," appears to be unphased by the provocation.");
	break;

	case -50..-25:
            actor("You growl as", ob, " taunts you back, provoking more hostility.");
            target(" growls as you taunt "+HIM(TP)+" back, provoking more hostility.", ob);
            all2act(" growls as",ob," taunts "+HIM(TP)+" back, provoking more hostility.");
	break;

	default:
            actor("You scream in anger as", ob, " ridicules your pathetic attempt at bravado.");
            target(" screams in anger as you ridicule "+HIS(TP)+" pathetic attempt at bravado.", ob);
            all2act(" screams in anger as",ob," ridicules "+HIS(TP)+" pathetic attempt at bravado.");
	break;
    }
    return 1;
}

int
emote_hscrape(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
       notify_fail("Hscrape at whom?\n");
       return 0;
    }

    ob = PARSE_THIS(str, "[at] %l");

    if(sizeof(ob))
    {
        obj = ob[0];

        actor("You slowly scrape your "+short()+" up and down creating a shrill irritating noise"+
              "", ob,"'s hair stands on end and shivers run down "+HIS(obj)+ " spine. ICK!!");
        target(" lowly scrapes "+HIS(TP)+" "+short()+" up and down creating a shrill irritating "+
               "noise. Your hair stands on end and shivers run down your spine. ICK!!", ob);
        all2act(" slowly scrapes "+HIS(TP)+ " "+short()+" up and down creating a shrill irritating "+
                "noise", ob,"'s hair stands on end and shivers run down "+HIS(obj)+ " spine. ICK!!");
        return 1;
    }

    write("You slowly scrape your "+short()+" up and down creating a shrill "+
          "irritating noise. ICK!!\n");
    say(QCTNAME(TP) + " slowly scrapes "+HIS(TP)+" "+short()+" up and down creating a "+
        "shrill irritating noise. Your hair stands on end and shivers "+
        "run down your spine. ICK!!\n");
    return 1;

}

int
emote_hpick(string str)
{
    if (str)
    {
       write("You only have to use 'hpick' without any arguments.\n");
    }
    if (!str)
    {
	write("You try to pick your nose with your "+short()+".\n");
	say(QCTNAME(TP) + " carelessly tries to pick "+HIS(TP)+ " nose with "+
            HIS(TP)+ " "+short()+". OUCH!!\n");
	return 1;
    }
    return 1;
}

void
init()
{
    ::init();
    add_action("emote_hsharpen", "hsharpen");
    add_action("emote_hinform" , "hinform");
    add_action("emote_hpick"   , "hpick");
    add_action("emote_hscrape" , "hscrape");
    add_action("emote_hshow"   , "hshow");
}
