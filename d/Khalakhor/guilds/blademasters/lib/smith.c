/*
 * smith.c
 *
 * Lib-type module which can be inherited into existing smiths to
 * turn them into blademaster smiths for the purposes of joining
 * and providing swords to blademasters, as well as special
 * clothing.
 *
 * Khail - Mar 4/97
 * Modified Dec 28 2001 by Teth - enabled all races to join
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/properties.h"

#define HIS_HER(x) x->query_possessive()

#define LIVE_O_SPOKE_TO_SMITH "_live_o_spoke_to_blademaster_smith"
#define LIVE_O_ASKED_JOIN     "_live_o_asked_to_join_blademasters"

public string
reply_thistle()
{
    command("emote glances about warily.");
    if (IS_BLADEMASTER(TP))
    {
        command("whisper " + OB_NAME(TP) + " Aye, I bear the " +
          "symbol of the Blademasters. My forge is yours.");
        return "";
    }
    command("whisper " + OB_NAME(TP) + " The thistle is a symbol " +
      "of the Blademasters.");
    return "";
}

public string
reply_blademasters()
{
    if (IS_BLADEMASTER(TP))
    {
        command("whisper " + OB_NAME(TP) + " There is nothing " +
          "I can tell you, that you do not already know, " +
          "Blademaster.");
        return "";
    }

    command("whisper " + OB_NAME(TP) + " The Blademasters are a " +
      "society, of sorts. Masters of the sword, they are, and " +
      "holders of old ways.");
    tell_room(environment(), QCTNAME(TO) + " glances over " +
      QTNAME(TP) + " carefully.\n", ({TP}));
    TP->catch_msg(QCTNAME(TO) + " glances over you carefully.\n");

    if (TP->query_base_skill(SS_WEP_SWORD) < JOIN_SWORD_SKILL)
    {
        command("whisper " + OB_NAME(TP) + " Far more skilled " +
          "than you, they are, I fear they would hold little " +
          "interest in you.");
        return "";
    }

    command("whisper " + OB_NAME(TP) + " Though possibly no " +
      "more skilled than you. You've the right to claim " +
      "the title of Blademaster, should you wish. Ask me " +
      "about their rules.");
      TP->add_prop(LIVE_O_SPOKE_TO_SMITH, TO);

    return "";

}

public string
reply_rules()
{
    if (!TP->query_prop(LIVE_O_SPOKE_TO_SMITH) ||
      TP->query_prop(LIVE_O_SPOKE_TO_SMITH) != TO)
    {
        command("whisper " + OB_NAME(TP) + " Rules? What rules?");
        return "";
    }

    command("smile knowingly");
    command("whisper " + OB_NAME(TP) + " There are few regulations " +
      "among the Blademasters, only old obligations of formality. " +
      "They were formed by a strange warrior from across the " +
      "waters a long time ago. Someone whose mastery of the " +
      "sword dwarfed the abilities of native warriors. He " +
      "first formed the Blademasters. First, you are required " +
      "to have exceedingly good sword abilities. Blademasters " +
      "must maintain a high level of skill with a sword. " +
      "If it falls, your right to the title is forfeit. " +
      "If this happens, " +
      "you will lose any experience learned as a Blademaster. " +
      "They provide no training, and there is no real place " +
      "they call home, only people like myself, who were " +
      "once Blademasters, who take care of the needs of the " +
      "current generation. It is not an occupation, rather " +
      "it is more like what people call a layman experience. " +
      "If you join, I can tell you more. If you leave immediately " +
      "after joining, there will be no loss.");
    return "";
}

public string
reply_join()
{
    object token,
    shadow;

    /* If the player is already a blademaster, do nothing. */
    if (IS_BLADEMASTER(TP))
    {
        command("whisper " + OB_NAME(TP) + " You are already " +
          "a Blademaster.");
        return "";
    }

    /* If the player has a blademaster bit, but for some */
    /* reason doesn't seem to be a blademaster, assume their */
    /* guild stuff was lost and try to replace it. */
    if (TP->test_bit("Khalakhor", IS_BLADEMASTER_BIT))
    {
        command("whisper " + OB_NAME(TP) + " Hmm, ok, let's " +
          "try this again.\n");
        seteuid(getuid());
        if (!IS_BLADEMASTER(TP))
        {
            shadow = clone_object(SHADOW);
            if (!shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
                GUILD_NAME, ""))
            {
                write("Couldn't let you join for some reason.\n");
                return "";
            }
        }
        TP->add_cmdsoul(SOUL);
        TP->update_hooks();
        if (!present(BLADEMASTER_CHAIN_NAME, TP))
            clone_object(TOKEN)->move(TP);
        return "";
    }

    if (!TP->query_prop(LIVE_O_SPOKE_TO_SMITH) ||
      TP->query_prop(LIVE_O_SPOKE_TO_SMITH) != TO)
    {
        command("whisper " + OB_NAME(TP) + " There's nothing " +
          "to say about that.\n");
        return "";
    }

    /* A little confirmation check so players don't join by */
    /* accident, they have to ask to join twice. */
    if (!TP->query_prop(LIVE_O_ASKED_JOIN))
    {
        command("whisper " + OB_NAME(TP) + " I can witness your " +
          "claim to your rightful title as Blademaster, if " +
          "you wish. Ask me again, and you'll be a Blademaster.");
        TP->add_prop(LIVE_O_ASKED_JOIN, TO);
        return "";
    }

    seteuid(getuid());
    shadow = clone_object(SHADOW);
    if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME, "")!=1)
    {
        write("You cannot join for some reason.\n");
        shadow->remove_shadow();
        return "";
    }
    TP->clear_guild_stat(SS_LAYMAN);
    command("smile warmly");
    command("say Let it be known that on this day, " +
      TP->query_name() + ", has claimed " + HIS_HER(TP) + " rightful place " +
      "among those who master the sword. Glory thy blade, " +
      "Blademaster!");
    seteuid(getuid());
    token = clone_object(TOKEN);
    token->move(TO, 1);
    command("whisper " + OB_NAME(TP) + " I believe these are yours.");
    token->remove_prop(OBJ_M_NO_DROP);
    command("give " + OB_NAME(token) + " to " + OB_NAME(TP));
    if (environment(token) == TO)
    {
        command("drop " + OB_NAME(token));
    }
    token->add_prop(OBJ_M_NO_DROP, 1);
    token = clone_object(JOIN_SCROLL);
    token->move(TO, 1);
    token->remove_prop(OBJ_M_NO_DROP);
    command("give " + OB_NAME(token) + " to " + OB_NAME(TP));
    if (environment(token) == TO)
    {
        command("drop " + OB_NAME(token));
    }
    token->add_prop(OBJ_M_NO_DROP, 1);
    log_file("blademasters/joined",TP->query_name() + " joined on " +
      ctime(time()) + ".\n");
    TP->add_cmdsoul(SOUL);
    TP->update_hooks();
    TP->set_bit(IS_BLADEMASTER_BIT);
    TP->remove_prop(LIVE_O_SPOKE_TO_SMITH);
    TP->remove_prop(LIVE_O_ASKED_JOIN);
    return "";
}

public string
reply_chain()
{
    object chain;

    /* Say nothing if the player isn't a blademaster. */
    if (!IS_BLADEMASTER(TP))
    {
        command("say What are you going on about chains for?");
        return "";
    }

    /* Do nothing if the player is a blademaster and still */
    /* has his chain. */
    if (present(BLADEMASTER_CHAIN_NAME, TP))
    {
        command("whisper " + OB_NAME(TP) + " You've still got your " +
          "chain, but if you ever lose it, I'll replace it for " +
          "you.");
        return "";
    }

    /* Replace missing chains for blademasters. */
    seteuid(getuid());
    chain = clone_object(TOKEN);
    chain->move(TO, 1);
    chain->remove_prop(OBJ_M_NO_DROP);
    command("give " + OB_NAME(chain) + " to " + OB_NAME(TP));
    if (environment(chain) == TO)
        command("drop " + OB_NAME(chain));
    chain->add_prop(OBJ_M_NO_DROP, 1);
    return "";
}

public string
reply_sword()
{
    /* Ignore questsions about swords from non-blademasters. */
    if (!IS_BLADEMASTER(TP))
    {
        command("say I don't have the vaguest idea what " +
          "you're talking about, sorry.");
        command("shrug");
        return "";
    }

    /* Tell blademasters he can make them a replacement sword. */
    command("whisper " + OB_NAME(TP) + " Aye, I can make you " +
      "a Blademaster sword. All you must do is 'request blade " +
      "be made from...' whatever sword you have with you. " +
      "I can convert most swords into Blademaster swords, " +
      "though some quality may be lost in the process.");
    return "";
}

public string
reply_clothes()
{
    /* Ignore questsions about clothes from non-blademasters. */
    if (!IS_BLADEMASTER(TP))
    {
        command("say I don't have the vaguest idea what " +
          "you're talking about, sorry.");
        command("shrug");
        return "";
    }

    command("whisper " + OB_NAME(TP) + " Aye, Blademaster. " +
      "I have a supply of traditional garb for a master. " +
      "Use 'blist' to see what I have available, and " +
      "'bbuy' to buy any of them.");
    return "";
}

public string
reply_start()
{
    /* Ignore questsions about clothes from non-blademasters. */
    if (!IS_BLADEMASTER(TP))
    {
        command("say I don't have the vaguest idea what " +
          "you're talking about, sorry.");
        command("shrug");
        return "";
    }

    command("smile proudly");
    command("whisper " + OB_NAME(TP) + " You wish to start " +
      "here in my forge? Of course! My home is yours!");
    TP->set_default_start_location(file_name(environment(TO)));
    return "";
}

public int
do_request(string str)
{
    object old_sword,
    new_sword;
    int new_hit,
    new_pen,
    recovery;

    if (!IS_BLADEMASTER(TP))
        return 0;

    NF("Request blade in exchange for what?\n");
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "'blade' 'in' 'exchange' 'for' " +
        "/ 'with' %o", old_sword))
        return 0;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("shout Why's it so bloody dark in here? I " +
          "can't see my hand in front of my face!");
        return 1;
    }

    if (!CAN_SEE(TO, TP))
    {
        command("say I cannae exchange anything with someone I cannae " +
          "see!");
        return 1;
    }

    if (old_sword->id(BLADEMASTER_SWORD_NAME))
    {
        command("whisper " + OB_NAME(TP) + " You want me to " +
          "exchange a Blademaster sword for a Blademaster sword?");
        command("peer " + OB_NAME(TP));
        command("whisper " + OB_NAME(TP) + " Taken one to many " +
          "blows to the head today, have we?");
        return 1;
    }

    if (old_sword->query_wt() != W_SWORD)
    {
        command("whisper " + OB_NAME(TP) + " I can hardly exchange " +
          "a Blademaster sword for that. I'll need a real sword " +
          "to exchange for a Blademaster sword.");
        return 1;
    }

    if (old_sword->query_likely_break() < 1)
    {
        command("whisper " + OB_NAME(TP) + " I have no swords akin to " +
          "that sword, the blade is too hard to be natural.");
        return 1;
    }

    if (old_sword->query_prop(WEP_I_BLADEMASTER_NO_EXCHANGE))
    {
        command("whisper " + OB_NAME(TP) + " I have nothing similar " +
          "to the power of that sword.");
        return 1;
    }

    if (old_sword->query_wielded())
    {
        command("whisper " + OB_NAME(TP) + " You'll have to let " +
          "go of the sword before I can exchange it.");
        return 1;
    }

    if (old_sword->query_prop(OBJ_I_BROKEN))
    {
        command("whisper " + OB_NAME(TP) + " I refuse to " +
          "exchange for a broken blade!");
        return 1;
    }

    if (old_sword->move(TO, 1))
    {
        command("whisper " + OB_NAME(TP) + " Hmm, I don't seem " +
          "to be able to take that sword from you, for some " +
          "reason.");
        return 1;
    }

    TP->catch_msg(QCTNAME(TO) + " reaches out his hand, and " +
      "you give him the " + old_sword->short() + ".\n");
    say(QCTNAME(TO) + " reaches out his hand, and " +
      QTNAME(TP) + " hands him " + LANG_ADDART(old_sword->short()) +
      ".\n");

    command("whisper " + OB_NAME(TP) + " This is your lucky day, " +
      "I believe. I just happen to have a Blademaster sword that " +
      "would be almost identical to anything I could make with " +
      "this weapon.");
    tell_room(environment(TO), QCTNAME(TO) + " places " +
      LANG_ADDART(old_sword->short()) + " away in a barrel of swords " +
      "behind him.\n");

    /* Here's where we make the Blademaster sword. Most of */
    /* the values are default, but the hands are set based on */
    /* the hands of the old sword, and the hit and pen values */
    /* are also based on the values of the old sword. Hit and */
    /* pen are capped, however, so that swords with a hit/pen */
    /* greater than 40 never produce as good a quality of */
    /* Blademaster sword. A sword with a pen of 60 would produce */
    /* a Blademaster sword with a pen of 50. if old = 80, new */
    /* = 60. */
    seteuid(getuid());
    new_sword = clone_object(WEP + "blade");
    new_sword->move(TO, 1);
    new_sword->set_hands(old_sword->query_hands());
    new_sword->set_may_not_recover();
    new_hit = old_sword->query_hit();
    new_hit = (new_hit <= 40 ? new_hit : 40 + (new_hit - 40) / 2);
    new_pen = old_sword->query_pen();
    new_pen = (new_pen <= 40 ? new_pen : 40 + (new_pen - 40) / 2);
    recovery = old_sword->check_recoverable();
    if (recovery)
    {
        new_sword->set_may_recover();
    }
    new_sword->set_hit(new_hit);
    new_sword->set_pen(new_pen);
    log_file("blademasters/sword_change",
             ctime(time()) + " " + TP->query_name() +
             " exchanged a " + file_name(old_sword) + " " +
             old_sword->query_hit() + " " + old_sword->query_pen() +
             " for a " + file_name(new_sword) + " " + new_sword->query_hit() +
             " " + new_sword->query_pen() + ".\n");
    old_sword->remove_object();

    tell_room(environment(), QCTNAME(TO) + " turns around and " +
      "retrieves " + LANG_ADDART(new_sword->short()) + " from " +
      "a cubby-hole behind him.\n");

    command("whisper " + OB_NAME(TP) + " Here you are, Blademaster!");
    command("give " + OB_NAME(new_sword) + " to " + OB_NAME(TP));
    if (environment(new_sword) == TO)
        command("drop " + OB_NAME(new_sword));
    return 1;
}


public void
create_bladesmith()
{
    TO->add_ask(({"thistle"}), VBFC_ME("reply_thistle"), 1);
    TO->add_ask(({"Blademasters", "blademasters"}),
      VBFC_ME("reply_blademasters"), 1);
    TO->add_ask(({"rules"}), VBFC_ME("reply_rules"), 1);
    TO->add_ask(({"join", "about joining", "to join", "joining"}),
      VBFC_ME("reply_join"), 1);
    TO->add_ask(({"chain"}), VBFC_ME("reply_chain"), 1);
    TO->add_ask(({"blademaster sword", "Blademaster sword"}),
      VBFC_ME("reply_sword"), 1);
    TO->add_ask(({"clothes","blademaster clothes","about clothes",
        "about blademaster clothes"}), VBFC_ME("reply_clothes"),1);
    TO->add_ask(({"start","startloc","start here","to start here"}),
      VBFC_ME("reply_start"), 1);
}

public int
do_blist(string str)
{
    command("whisper to " + OB_NAME(TP) + " I have the following " +
      "clothing for you.");
    write("  black leather boots       95 copper\n" +
      "  black leather gloves      60 copper\n" +
      "  blademaster kilt         120 copper\n" +
      "  blademaster dress        120 copper\n" +
      "  thick black shirt        120 copper\n");
    return 1;
}

public int
do_bbuy(string str)
{
    string file;
    object armour;
    int price;

    if (!str || !strlen(str))
    {
        NF("Bbuy what?\n");
        return 0;
    }

    if (parse_command(str, TP, "[black] [leather] 'boots'"))
        file = ARM + "boots";
    else if (parse_command(str, TP, "[black] [leather] 'gloves'"))
        file = ARM + "gloves";
    else if (parse_command(str, TP, "[blademaster] 'kilt'"))
        file = ARM + "blademaster_kilt";
    else if (parse_command(str, TP, "[blademaster] 'dress'"))
        file = ARM + "dress";
    else if (parse_command(str, TP, "[thick] [black] 'shirt'"))
        file = ARM + "shirt";

    if (!file)
    {
        command("whisper to " + OB_NAME(TP) + " I don't have " +
          LANG_ADDART(str) + "!");
        return 1;
    }

    armour = clone_object(file);
    price = armour->query_prop(OBJ_I_VALUE);

    if (!MONEY_ADD(TP, -price))
    {
        command("whisper to " + OB_NAME(TP) + " As much as I'd " +
          "like to just give this to a Blademaster, I have to " +
          "buy them myself, and can't afford charity. Come back " +
          "when you have more money, I'll still have it for " +
          "you.");
        armour->remove_object();
        return 1;
    }

    if (armour->move(TP))
    {
        command("whisper to " + OB_NAME(TP) + " Hmm, seems I can't " +
          "give it to you for some reason. Try lightening your " +
          "load and buying it again.");
        armour->remove_object();
        MONEY_ADD(TP, price);
        return 1;
    }

    write(TO->query_The_name(TP) + " takes your money and hands " +
      "you a brand new " + armour->short() + ".\n");
    tell_room(environment(TO), QCTNAME(TO) + " exchanges some " +
      "money with " + QTNAME(TP) + " for a black bundle.\n", TP);
    return 1;
}

public void
init_bladesmith()
{
    add_action(do_request, "request");
    add_action(do_blist, "blist");
    add_action(do_bbuy, "bbuy");
}
