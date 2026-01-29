	
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include <wa_types.h>

#define  WEP1           (WEP    + "iron_axe")
#define  ARM1           (ARMOUR + "chainmail")
#define  ARM2           (ARMOUR + "leggings")
#define  ARM3           (ARMOUR + "i_gauntlets")
#define  ARM6           (ARMOUR + "i_boots")
#define  ARM4           (ARMOUR + "shield")
#define  ARM5           (ARMOUR + "horned_helmet")

#define NEIDAR_CLAN     "Dwarven Warriors of the Neidar Clan"
#define LOG_DIR         "/d/Ansalon/guild/shieldbearers/log/"

inherit  AM_FILE
inherit  "/d/Krynn/std/equip";

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("gorrthaur");
    add_name("trainer");
    set_living_name("gorrthaur");
    set_title("Strongarm, Veteran Shieldbearer of Iron Delving");
    set_race_name("dwarf");
    set_adj("old");
    add_adj("curly-bearded");
    set_gender("G_MALE");
    set_long("This is an old dwarven warrior who trains clan " +
      "members the skills needed to survive the rugged lands " +
      "of Estwilde. He looks as gnarled and old as an ancient tree stump, " +
      "but you have no doubt that he could still hack down an " +
      "ogre or two.\nHe is wearing insignia of the Bronze Buckler.\n");

    set_stats( ({ 160, 120, 170, 90, 90, 130 }) );

    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    set_alignment(100);
    set_knight_prestige(-1);
    set_introduce(1);

    set_default_answer("The dwarf looks at you funnily, as if " +
        "you should already know the answer to that.\n");
        
    add_ask(({ "shieldbearers", "Shieldbearers", "guild", 
        "shieldbearer", "Shieldbearer" }), "@@ask_guild", 1);
    add_ask(({ "list", "members", "members list"}), "@@ask_members", 1);
    add_ask(({ "training", "joining", "join", "train" }), "@@ask_join", 1);
    add_ask( "leaving", "say If ye don't want to be a shieldbearer " +
        "any more just return yer insignia. Ye will forget how to use " +
        "the ability I teach here, however.", 1);
    add_ask(({ "ability", "abilities", "slam", "shieldslam", "trick", 
        "shield", "skills", "skill" }),
        "say I can teach ye how to use yer shield not only for " +
        "defending yerself. Ye will be shown how to appraise yer " +
        "enemy and how to grip an axe, just in case.", 1);
    add_ask(({ "race", "races", "tall races" }),
        "say I do not trust all thos' tall races and I will not teach " +
        "'em nothing! Only gnomes, kenders, hobbits and of course " +
        "dwarves shall train 'ere!", 1);
    add_ask(({ "friend", "friends", "neidar friends" }),
        "say Only the fellow clansmen and thos' who bear the token of " +
        "our friendship shall be allowed to train with me! But I will not " +
        "teach anythin' to mountain scums, 'umans, elves and the rest " +
        "of the tall folk!", 1);
    add_ask(({ "boulder", "large boulder", "stone", "rock", 
        "granite boulder" }), "say Well, ye can always charge at it! " +
        "Ma'be ye will learn somethin' ma'be not! But surely ..." +
        "it will be fun!", 1);
        
    set_act_time(6);
    add_act("say Those youn' warriors do not know how to use shields! " +
        "Good they use 'em at all!");
    add_act("say Nothin' is better for my ol' bones than bashin' an ogre " +
        "or two with the shield! That keeps me in shape.");
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
        "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his curled beard lovingly.");
    add_act("say Try chargin' at the boulder! Ma'be ye will learn somethin'.");
    add_act("emote thinks hard about the boulder.");
    add_act("emote looks around like he was searching for something.");
    add_act("emote giggles. You wonder what he is thinking about.");

    set_cact_time(0);
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");

    seteuid(getuid(TO));
    equip(({ WEP1, ARM1, ARM2, ARM3, ARM4, ARM5, ARM6 }));
}

public string
ask_guild()
{
    command("emote tugs his beard.");
    command("say Shieldbearers? I guess ye ar' speakin' of the trick I " +
        "teach to som' of the clansmen? Most of 'em ar' good warriors but " +
        "it aint easy to win the battle if ye lose yer weapon for som' " +
        "reason! Then yer best friend is yer shield. Remember that, " +
        ((TP->query_gender() == 0) ? "boy!" : "lad!")); 
        
    if (TP->query_guild_member(NEIDAR_CLAN) || TP->test_bit("Ansalon", 3, 13))
    {
        command("say Hmm, if ye ar interested in training, I could tell ye " +
            "more 'bout it.");
    }
    else
    {
        command("say Hmm, ye don't look like someone I shoul' tell more " +
            "'bout the training!");
    }
    
    if ( TP->test_bit("Ansalon", 3, 4) || TP->test_bit("Ansalon", 3, 3) ||
        TP->query_wiz_level() )
    {
        TP->catch_msg(QCTNAME(TO) + " whispers to you: If ye wanna know " +
            "the names of those, who trained with me, just ask me " +
            "about members.\n");
    }
    
    return "";
}

public string
ask_members()
{
    mixed  names, names_tmp = ({});
    string members = "", name, t;
    int    size, i = -1, pos;
            
    if ( !TP->test_bit("Ansalon", 3, 4) && !TP->test_bit("Ansalon", 3, 3) &&
        !TP->query_wiz_level() )
    {
        command("emote stubbornly refuses to answer that question.");
        return "";
    }
    
    names = explode(read_file(LOG_DIR + "members_list"), "\n");
    
    size = sizeof(names);
    
    while(++i < size)
    {
        if ((pos = sscanf(names[i], "%s left %s", name, t)) == 2)
        {
            if ((pos = member_array(name, names_tmp)) != -1)
                names_tmp = exclude_array(names_tmp, pos, pos);
        }
        else
        {
            if (sscanf(names[i], "%s joined %s", name, t) == 2)
                if (member_array(name, names_tmp) == -1)
                    names_tmp += ({ name });
        }
    }
    
    if ( !sizeof(names_tmp) )
    {
        TP->catch_msg(QCTNAME(TO) + " whispers to you: Woulde ye belive? " +
            "Noone wants to train with me!\n");
        return "";
    }

    members = sort_array(names_tmp);    
    members = implode(names_tmp, ", ");
    
    command("hmm");
    TP->catch_msg(QCTNAME(TO) + " whispers to you: These are names I " +
        "do remember... " + members + ".\n");
        
    return "";            
    
}

public string
ask_join()
{
    if (TP->query_guild_member(NEIDAR_CLAN) || TP->test_bit("Ansalon", 3, 13))
    { 
        command("say If ye want I can teach ye how to slam yer enemy " +
            "with yer shield. That ain't easy to master but he may have " +
            "problems with standin' against ye if ye bash him nicely. " +
            "However, only Neidars and our good friends may train here! " +
            "I don't trust those tall races an' I'll teach 'em nothin' as " +
            "they may betray us easily!"); 
        command("say So? If ye ar' interested in becomin' a shieldbearer, " +
            "just do it and I'll show ye how it works!");
    }
    else
    {
        command("say I teach only clanmembers and our good friends. If ye " +
            "can prove we can trust ye then fine. But ye shoul' speak with " +
            "the Thane or Elders first. Till then I will teach ye nothin'.");
    }

    return "";
} 

int
special_attack(object enemy)
{
    int   attacktype,
    pen,
    wloc,
    stun_duration;

    mixed hitres;

    string *hitloc,
    how,
    weapon,
    shield_short;

    if(!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 350 + random(200);

	hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

	wloc = random(5);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " just missing";
	if (hitres[0] > 0)
	    how = "his " + weapon + " grazing the skin of";
	if (hitres[0] > 10)
	    how = "slicing his " + weapon + " deeply into";
	if (hitres[0] > 20)
	    how = "his " + weapon + " deeply penetrating";
	if (hitres[0] > 40)
	    how = "burying his " + weapon + "deeply into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " splattering blood everywhere " +
	    "as he almost removes";

	enemy->catch_msg(QCTNAME(TO) + " charges at " +
	  "you in a furious attack, " + how + " your "
	  + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " charges at " + QCTNAME(enemy)
	  + " in a furious rage, " + how + " " + QCTNAME(enemy) + "'s" +
	  " " + hitloc[wloc] + ".\n", ({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    
    if ( attacktype == 2 )
    {
        if(TO->query_armour(W_RIGHT)->query_at() == A_SHIELD)
        {
            shield_short = TO->query_armour(W_RIGHT)->short();
        }
        else if(TO->query_armour(W_LEFT)->query_at() == A_SHIELD)
        {
            shield_short = TO->query_armour(W_LEFT)->short();
        }
        else
            return 0;
                                                            
        if ( !random(3) )
        {
            enemy->catch_msg("With a roar, " + QTNAME(TO) + " charges " +
                "past you, missing you with " + HIS(TO) + " " + 
                shield_short + ".\n");
            tell_room(E(TO), "With a roar, " + QTNAME(TO) + " charges " +
                "past " + QTNAME(enemy) + ", missing " + HIM(enemy) + 
                " with " + HIS(TO) + " " + shield_short + ".\n", enemy);
        }
        else
        {
            enemy->catch_msg("With a roar, " + QTNAME(TO) + " charges " +
                "into you, slamming you with " + HIS(TO) + " " + 
                shield_short + ".\n");
            tell_room(E(TO), "With a roar, " + QTNAME(TO) + " charges into " +
                QTNAME(enemy) + ", slamming " + HIM(enemy) + " with " +
                HIS(TO) + " " + shield_short + ".\n", enemy);
        
            pen = 450;
            hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);        
            
            if (enemy->query_hp() <= 0)
            {
                 enemy->do_die(TO);

                 return 1;
            }
                                        
            stun_duration = 4 + random(7);
          
            enemy->add_attack_delay(stun_duration, 1);
        }     
    }
    
    return 0;
}

void
attacked_by(object ob)
{
    ob->add_prop(DWARF_ENEMY, 1);

    command("shout Iron Delving! To arms!");

    ::attacked_by(ob);
}
                