/* file name:        /d/Avenir/common/holm/t_camp/trolgen.c
 *  creator(s):      Rangorn , Feb 97
 *  revisions:       Rangorn , July 97
 *  purpose:   This is a standard module for making aggressive trolobys
 *             for the  troloby camp on the holm.                                                        
 *  note:
 *  bug(s):
 *  to-do:
 */                                                                      

inherit "/std/monster";

#include "/d/Avenir/common/holm/holm.h"
#include "/d/Genesis/gems/gem.h"
#include <ss_types.h>
inherit "/d/Avenir/inherit/helper";

#define FIXEUID   setuid(); seteuid(getuid())

string *adj1, *adj2, *atts, att;
string my_long();
void   set_attribute(string str) {    att = str;    }

void
create_monster()
{
    int stat;

    adj1 = ({"lean","well-built","huge","fleshy","wiry","barrel-chested", 
             "long-legged","muscular","thick-armed", "smelly", "limping",
             "youthful", "young", "aged"});
    adj2 = ({"pointy-eared","broad-nosed","yellow-eyed","grinning","angry",
             "hungry","flat-nosed","pink-eyed","fanged","thick-lipped"});
    atts = ({"ram's horns curling down over its ears", 
             "a pig's snout for a nose", "a huge, bulbous nose",
             "eyes large as apples with very long lashes", 
             "absurdly small ears tipped with white fuzz",
             "a skeletal pincer where its right hand should be",
             "hooves instead of feet", "backward-bending elbows and "+
             "knees", "one arm that is longer than the other",
             "delicate, extremely long-fingered hands" }); 
              
    stat=random(50);
    set_name("wild troloby");
    add_name(({"a_troloby_in_the_troloby_camp", "impure"}));
    set_race_name("troloby");
    set_gender(G_NEUTER);
    set_adj(adj1[random(sizeof(adj1))]);
    set_adj(adj2[random(sizeof(adj2))]);
    set_attribute(atts[random(sizeof(atts))]);
    set_pick_up(1);
    set_long(my_long);

    default_config_npc(random(50) + 75);

    set_skill(SS_BLIND_COMBAT, 40+random(20));
    set_skill(SS_DEFENCE, 50+random(30));
    set_skill(SS_WEP_CLUB, 70 + random(20));
    set_skill(SS_AWARENESS, 40 + random(20));
    set_scar(random(20));
    set_pick_up(1);
    set_attack_chance(50);

    add_prop(LIVE_I_NEVERKNOWN, 1);  
    add_prop(NPC_I_NO_FEAR, 1);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    if (random(5)) 
        add_leftover("/d/Avenir/inherit/leftover", "skin",1, "", 0,0);
   
    set_act_time(8);
    add_act("fume");
    add_act("grin pain");
    add_act("emote rubs its rumbling stomach.");
    add_act("emote stares at you with empty eyes.");
    add_act("emote shakes violently with spasmodic convulsions.");     
    add_act("emote looks up at the source and mumbles something.");    
    add_act("emote sniffs hungrily at the air.");
    add_act("nod vig");

    set_chat_time(5);
    add_chat("All of us are very grateful to our master.");
    add_chat("Soon we will hold the final ritual.");    
    add_chat("Something smells tasty!");
    add_chat("Master wants us to trap one of the Pure.");
    add_chat("I still think it's time for another raid on the bicorns.");
    add_chat("We got two bicorns left, and I could eat one myself.");
    add_chat("Master has made my impure existence worth living.");
    add_chat("Those infidels are tasty.");
    add_chat("I say we toss some caltrops around, wait for a shadow "+
        "elf to hurt himself, then drag him to the wizard.");

    set_cchat_time(4);
    add_cchat("I will kill you.");   
    add_cchat("You're a fool to come here.");
    add_cchat("Now the hunted becomes the hunter.");
    add_cchat("You'll make a fine addition to the dinner pot.");
    
    // Make the trolobys walk around in the camp.
    set_restrain_path(({"/d/Avenir/common/holm/t_camp", 
                        "/d/Avenir/common/holm/shore", 
                        "/d/Avenir/common/holm/jungle" }));
    set_monster_home(T_CAMP + "c6");
    set_random_move(25 + random(7));
    set_helper_friends ( ({"troloby"}) );

    add_ask(({"mage","Mage","master","Master","hunchbacked human",
        "wizard", "Wizard", "Nemur", "nemur"}),
        "say He is the one who assisted in my transition into this "+
        "life. Nemur is a powerful wizard, dwelling in safety beyond "+
        "the crack.", 1);
    add_ask(({"crack", "chasm", "tent"}),
        "say The crack in the bedrock was created by my Master when he "+
        "unleashed some unnatural power.", 1);
    add_ask(({"pure","Pure", "pure ones", "Pure Ones", "banishment"}),
        "say I am too unpleasant to look upon, so they keep me here.",1);
    add_ask(({"impure","Impure"}),
        "say I am Impure. My master gives me hope that one day I will be free "+
        "of the impurities that have resulted in my banishment.",1);
    add_ask(({"hunt","Hunt"}),
        "say The Pure come here every now and then to Hunt us just " +
        "for fun and their personal pleasure.",1);   
    add_ask(({"Troloby","troloby","trolobys","Trolobys"}),
        "say That is what the Pure Ones calls us.",1);
    refresh_mobile();
}

string
my_long()
{
    string str;
    str = "It is "+ LANG_ADDART(implode(query_adjs(), " ")) +
           " wild "+ query_race_name()+".\n";

    str += "It appears to be of mixed heritage, perhaps even mixed species. "+
           "Although it resembles a very large human, there is no doubt that "+
           "something terrible has been done to it.\n"+
           "Its skin is pale pink, with traces of a sickly yellow color "+
           "running along it in twisted patterns.\n" +
           "There is a zealous, barely-sane gleam in its eyes.\n"+
           "It has "+ att +".\n";

    return str;
}

public void
add_introduced(string name)
{
    command("say Your name is of no interest to me.");
}

public void
equip_me()
{
    object leather_tunic, cesti, caltrop, club, gem;
    int i = random(10);
    FIXEUID;

    leather_tunic = clone_object(HOLM_OBJ + "leather");
    leather_tunic->move(this_object());                 
    
    if (random(2))
    {
        gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
        gem->move(this_object());    
    }

    if (i < 5)
        club = clone_object(HOLM_OBJ + "trol_club")->move(this_object());
    if (i > 5)
    {
        set_skill(SS_UNARM_COMBAT, 60 + random(20));        
        cesti = clone_object(HOLM_OBJ + "cesti")->move(this_object());                 
    }
    if (i > 8)
        caltrop = clone_object(HOLM_OBJ + "caltrop")->move(this_object());
    command("wear all");
    command("wield all");
}

void
throw_myself(object ob)
{
    object          *enemies, *ene;
    int             i, j, hp, max;
    string          rescue, *rescue2;

    if (!present(ob, environment(this_object())))
        return;

    enemies = all_inventory(environment(this_object())) - 
              ({ ob, this_object() });

    for (i = 0; i < sizeof(enemies); i++)
    if (enemies[i]->query_attack() == ob)
    {
        this_object()->attack_object(enemies[i]);
        enemies[i]->attack_object(this_object());
    }
}


void
do_kill(object pl)
{
    command("kill "+ pl->query_name());
}

void
init_living()
{
    ::init_living();

    if (TP->id("noble"))
    {
        run_away();
        run_away();
        return;
    }        
    if (interactive(TP) && CAN_SEE(TO, TP))
        set_alarm(1.5, 0.0, &do_kill(TP));


}  

