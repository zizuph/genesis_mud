#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <const.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <money.h>

inherit "/d/Krynn/std/monster";

#define WEP_STAFF    "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define VEST         "/d/Krynn/haven/town/arm/vest"
#define HERB_POUCH   "/d/Gondor/common/obj/herbpouch"
#define SATCHEL      "/d/Gondor/common/potions/satchel"
#define BOOTS        "/d/Ansalon/taman_busuk/neraka/arm/boots1"
#define BREECHES     "/d/Ansalon/taman_busuk/neraka/arm/breeches"
#define BELT         "/d/Ansalon/taman_busuk/neraka/arm/lbelt"

#define MANA_SHADOW       "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define DIALOG_PROP       "_parsalian_currently_dialoguing"
#define INTRO_TO_ASPIRANT "_wohs_test_parsalian_introduced"
#define LEFT_TEST         "_wohs_test_left_test"
#define FINISHED_TEST     "_wohs_test_finished_test"

void get_me_soul();
void arm_me();

int soul_id;
static int dialog_alarm;
public object dialog_target;
static mapping speak;

public varargs int
handle_timed_messages(object player, mapping messages, int cycle)
{
    if (objectp(dialog_target))
    {
        if (!present(dialog_target, environment(this_object())))
        {
            command("emote stops his conversation as the person he was " +
               "talking to leaves.");
            // Rude to leave like that while someone is lecturing.
            remove_alarm(dialog_alarm);
            dialog_target = 0;
        }

        if (objectp(dialog_target) && !cycle)
        {
            command("wfrown");
            // Interrupting conversation, thats not very nice.
            return 0;
        }

        if (!objectp(dialog_target))
            return 1;
    }

    if (!CAN_SEE(this_object(), player))
    {
        command("say It would be best if you revealed yourself rather " +
            "than remain hidden. I find a conversation is more " +
            "congenial when I can see who I am talking to.");
        remove_alarm(dialog_alarm);
        dialog_target = 0;
        return 0;
    }

    if (!mappingp(messages) || !m_sizeof(messages))
        return 1;

    // Deliver the message
    if (cycle)
        command(messages[cycle][1]);

    dialog_target = player;
    cycle++;

    if (member_array(cycle, m_indexes(messages)) < 0)
    {
        remove_alarm(dialog_alarm);
        dialog_target = 0;
        return 1;
    }

    dialog_alarm = set_alarm(messages[cycle][0], 0.0,
                     &handle_timed_messages(player, messages, cycle));
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("par-Salian");
    add_name("par-salian");
    set_living_name("par-salian");
    set_title("of Wayreth, Highmage of the Wizards of High Sorcery, " +
        "Head of the Conclave");
    set_race_name("human");
    set_adj("frail");
    add_adj("elderly");
    set_gender("G_MALE");
    set_long("Before you stands a white robed, frail, elderly-looking " +
        "man who appears to be in his seventies, with long wispy white " +
        "hair and a long white beard. His bright blue eyes give lie to " +
        "his frail appearance however - windows to knowledge and " +
        "magical power unmatched by anyone on Krynn. This man is " +
        "the Head of the Conclave of the Wizards of High Sorcery and " +
        "Master of the Tower of Wayreth.\n");

    set_stats(({160,160,400,300,300,160}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(OBJ_M_NO_ATTACK,"Spells and wards protect him from being " +
        "attacked, making him almost invincible within the walls of " +
        "the Tower of Wayreth.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_AIR, 100);

    add_prop(OBJ_I_RES_POISON, 100);

    set_all_hitloc_unarmed(90);

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    // set_alarm(0.0, 0.0, arm_me);

    trig_new("%w 'introduces' %s","react_to_intro");

    set_alignment(1200);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"test","test of high sorcery","challenges","challenge",
        "trials","trial"}), VBFC_ME("test_hint"));
    add_ask(({"magic","high sorcery","sorcery",
        "arcane magic","art","art of high sorcery"}),
        VBFC_ME("magic_hint"));
    add_ask(({"gods of magic","gods","lunitari","solinari","nuitari"}),
        VBFC_ME("gods_hint"));
    add_ask(({"shadows","west"}),"say By entering the shadows " +
        "you begin the Test. There is no turning back at that " +
        "point.", 1);
    add_ask(({"quest"}),"say I have no quest for you, although I have " +
        "heard disturbing reports of the return of the cladestine " +
        "group of renegades known as the Obsidian Circle within the " +
        "Tharkadan mountain range to the south of Pax Tharkas. It may " +
        "be worth investigating.", 1);
    add_ask(({"spell","teach magic","teach spell","spells"}),
        VBFC_ME("spell_hint"));
    add_ask(({"help","trials"}),VBFC_ME("help_hint"));
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);

    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

string
default_answer()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    if(random(2))
    {
        command("ponder");
        command("say I don't have an answer for you on that. Yet.");
        command("smile mysterious");
        return "";
    }
    else if(random(2))
    {
        command("smile thought");
        command("say I think that is a question best answered through " +
            "your own trials and deliberations.");
        return "";
    }

    command("emote contemplates the question.");
    command("say A good question...");
    command("say Although I have no answer to it for you.");
    return "";
}

string
test_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
            "someone else. You should wait until he is finished.\n";

    speak = ([
        1 : ({ 0.5, "say The Test is much more than a simple trial of " +
                    "magical ability."}),
        2 : ({ 3.0, "say It seeks to assess a wizard's spirit and " +
                    "ultimate potential, forcing each hopeful to look " +
                    "within himself to assess his dedication to magic, " +
                    "his strengths and weaknesses, and his sense of " +
                    "where the path of High Sorcery might lead him."}),
        3 : ({ 7.0, "say And in the end, the Test asks two questions of " +
                    "each person who takes it... "}),
        4 : ({ 5.0, "say Are there any things more important to you " +
                    "than the gift of magic?"}),
        5 : ({ 5.0, "say And, when called upon, will you sacrifice " +
                    "those things for the Art?"}),
        6 : ({ 4.0, "say Understand that for those who fail the Test, " +
                    "death is the only outcome, for wizards long-ago " +
                    "judged it better to allow unfocused or " +
                    "undisciplined students to die rather than give " +
                    "their skills the chance to do harm."}),
        7 : ({ 8.0, "say And for those who pass, the Test often " +
                    "inflicts scars - both physical and emotional - " +
                    "which will mark the wizards as surely as the " +
                    "colour of the robes most will wear for the rest " +
                    "of their lives."}),
        8 : ({ 8.0, "say Those who make the journey and take the Test " +
                    "undergo a trial of skill and nerve that is an " +
                    "experience shared by wizards, and allows a Black " +
                    "Robe to have moments of understanding with those " +
                    "who wear raiment of White."}),
        9 : ({ 8.0, "say The Test of High Sorcery is the single binding " +
                    "experience in a wizard's life that makes all " +
                    "Wizards of High Sorcery brothers and sisters " +
                    "in magic."}),
       10 : ({ 8.0, "say A wizard's soul is forged within the fires of " +
                    "magic, and they will never be the same again."}),
       11 : ({ 5.0, "say So if you still intend to undertake the Test, " +
                    "you may begin it by entering the shadows to your " +
                    "west."}),
       12 : ({ 5.0, "say Good fortune in your trials!"}),
    ]);

    handle_timed_messages(this_player(), speak);

    return "";
}

string
magic_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    speak = ([
        1 : ({ 0.5, "say In broadest terms, magic is the power to " +
                    "manipulate the very fabric of creation itself."}),
        2 : ({ 5.0, "say An intrinsic part of the universe, designed " +
                    "and shaped by the gods themselves, magic may be " +
                    "used as a tool for good and the betterment of " +
                    "the world - or it can be brandished as a weapon " +
                    "capable of laying whole nations low."}),
        3 : ({ 7.0, "say And while many view a force of such " +
                    "extraordinary magnitude as too potent a power to " +
                    "be wielded by merely mortal hands, it " +
                    "is mortals to whom magic is ultimately bound."}),
        4 : ({ 7.0, "say The arcane power of Krynn is refined and " +
                    "explored over generations by those with the " +
                    "talent, the courage, and the fortitude to wield it."}),
        5 : ({ 7.0, "say Arcane magic deals with forces so potent that " +
                    "it took the guiding hands of the Gods of Magic to " +
                    "instruct mortals in its proper use, and the Art " +
                    "of High Sorcery is the lasting legacy of " +
                    "this divine instruction."}),
        6 : ({ 10.0,"say The Gods of Magic bestowed upon the world the " +
                    "methods of tapping, manipulating, and, most " +
                    "importantly, harnessing raw arcane energy, using " +
                    "formulas and exacting rituals designed to " +
                    "keep the manifestation of arcane power out of " +
                    "rash and careless hands."}),
        7 : ({ 7.0, "say It is this gift of magic that has become the " +
                    "dominion of wizards throughout Krynn, and " +
                    "ultimately their duty to protect."}),
    ]);

    handle_timed_messages(this_player(), speak);

    return "";
}

string
gods_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    speak = ([
        1 : ({ 0.5, "say You wish to speak theology? I hope you haven't " +
                    "mistaken the tower for a place of worship!"}),
        2 : ({ 1.5, "smile amusedly"}),
        3 : ({ 3.0, "say In seriousness, it is a good question. There " +
                    "are three Gods of Magic - three cousins in fact."}),
        4 : ({ 4.0, "say Solinari, God of the Silver Moon, ruler of " +
                    "the Magic of Light."}),
        5 : ({ 4.0, "say Lunitari, Goddess of the Red Moon, ruler of " +
                    "the Magic of Neutrality..."}),
        6 : ({ 4.0, "say ... and Nuitari the God of the Dark Moon - a " +
                    "moon that can be seen only by his followers - a " +
                    "god of mystery and shadow."}),
        7 : ({ 6.0, "say Although each of the Gods of Magic has his or " +
                    "her own alignment, the gods share a single " +
                    "allegiance: magic."}),
        8 : ({ 6.0, "say Thus it is that the Gods of Magic often ally " +
                    "one with the other to stand together either in " +
                    "favour of, or in opposition to, the rest of the " +
                    "pantheon. This united voice gives them strength " +
                    "often lacking in the divisive clamor of the other " +
                    "gods."}),
        9 : ({ 12.0, "say This is not to say that there is not some " +
                    "rivalry between the Three Cousins. Each god is " +
                    "intent on promoting his own cause, and on assisting " +
                    "his own followers to gain power and knowledge."}),
       10 : ({ 12.0, "say Their rivalry is keen, but not bitter. No " +
                    "matter what single objective each of the gods may " +
                    "pursue, they remain united in one common goal and " +
                    "that is the promotion and regulation of magic."}),
       11 : ({ 12.0, "say To this end, the gods established the Orders " +
                    "of High Sorcery, wherein practitioners of magic " +
                    "would come together in Conclave to pass laws that " +
                    "govern themselves and to try to maintain control " +
                    "over all those who wield magic."}),
    ]);

    handle_timed_messages(this_player(), speak);

    return "";
}

string
spell_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    if(WOHS_MANAGER->query_scribed_spell(this_player(),"nuadealdoer"))
    {
        speak = ([
        1 : ({ 0.5, "emote runs a hand thoughtfully through his whispy " +
                    "white hair."}),
        2 : ({ 1.5, "say I have nothing further I wish to teach you."}),
        3 : ({ 3.0, "say If you haven't already, I suggest doing some " +
                    "spell research in the library here in the Tower."}),
        4 : ({ 2.0, "say Or perhaps consider taking a trip " +
                    "to Palanthas? Some fine spell tomes used to be " +
                    "purchasable at Zeb's Unlooked for Tomes."}),
        ]);

    }
    else if(QUERY_IS_ARCHMAGE(this_player()) ||
        QUERY_WHITE_COUNCIL(this_player()) ||
        QUERY_RED_COUNCIL(this_player()) ||
        QUERY_BLACK_COUNCIL(this_player()))
    {
        speak = ([
        1 : ({ 0.5, "say Yes, I think I could share with you a spell " +
                    "reserved for only the most senior of Archmages " +
                    "and Conclave members."}),
        2 : ({ 5.0, "say Nuadealdoer, the Rune of Welcome, a simple " +
                    "yet closely guarded spell that allows the caster " +
                    "to mark someone with a rune, allowing them to pass " +
                    "through the magical guardian forest of Wayreth to " +
                    "the Tower of High Sorcery."}),
        3 : ({ 10.0, "say I am sure you will use it wisely!"}),
        4 : ({ 3.0, "emote murmurs a few spidery words of magic and " +
                    "gestures towards you."}),
        5 : ({ 4.0, "say There. You should find it now scribed in your " +
                    "spellbook."}),
        6 : ({ 3.0,"wink . "}),
        ]);

        WOHS_MANAGER->scribe_spell_to_spellbook(this_player(),"nuadealdoer");
    }
    else if(WOHS_IS_MEMBER(this_player()))
    {
        speak = ([
        1 : ({ 0.5, "ponder"}),
        2 : ({ 2.0, "say I have no spells to share with you at this " +
                    "time. Perhaps return to me when you have reached " +
                    "a certain seniority within your Order."}),
        3 : ({ 2.0, "say In the meantime, perhaps consider taking a trip " +
                    "to Palanthas? Some fine spell tomes used to be " +
                    "purchasable at Zeb's Unlooked for Tomes."}),
        ]);
    }
    else
    {
        speak = ([
        1 : ({ 0.5, "smile ."}),
        2 : ({ 2.0, "say I would be remiss in my duty to the protection " +
                    "of magic if I trained one who has not passed the " +
                    "Test of High Sorcery."}),
        3 : ({ 2.0, "say Perhaps seek out someone prepared to sell you " +
                    "some more common spells? Some fine tomes used to be " +
                    "purchasable at Zeb's Unlooked for Tomes in Palanthas."}),
        ]);
    }
    handle_timed_messages(this_player(), speak);

    return "";
}


string
help_hint()
{
    if (!handle_timed_messages(this_player()))
        return C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n";

    speak = ([
        1 : ({ 0.5, "say I can only give you general advice about the " +
                    "trials you may face in the Test of High Sorcery."}),
        2 : ({ 1.5, "say The overriding goal of the Test of High " +
                    "Sorcery is to assure that wizards who will be " +
                    "given access to powerful arcane spells are serious " +
                    "about the practice of magic and will use it " +
                    "responsibly."}),
        3 : ({ 7.0, "say A supplicant mage taking the Test risks his " +
                    "life in doing so, and thereby pledges his life to " +
                    "the practice of magic and the Orders of High " +
                    "Sorcery."}),
        4 : ({ 9.0, "say The inherent risk involved in the testing " +
                    "process serves a simple principle: anyone wishing " +
                    "to learn more advanced spells must take the " +
                    "responsibility seriously enough to stake his life " +
                    "on the chance to attain such power."}),
        5 : ({ 9.0, "say One important aspect of the Test is the moral " +
                    "choices it presents to the wizard. A mage who " +
                    "survives the Test will wear the white, red, or " +
                    "black robes and be a full member of the respective " +
                    "Order, aligned with a moon and God of Magic."}),
        6 : ({ 9.0, "say Those choices made during the Test will define " +
                    "the wizard's place within the Orders of High " +
                    "Sorcery."}),
        7 : ({ 5.0, "say A fundamental part of the Test is the simple " +
                    "examination of the wizard's magical skills. That " +
                    "should be no surprise to you."}),
        8 : ({ 9.0, "say Finally, the ability to solve problems and " +
                    "situations without the use of magic. The Orders of " +
                    "High Sorcery understand that not every problem " +
                    "can be solved with a spell, and that a candidate " +
                    "should demonstrate common sense and " +
                    "resourcefulness."}),
        9 : ({ 6.0, "say And that is all I will speak of about the " +
                    "trials you will face."}),

    ]);

    handle_timed_messages(this_player(), speak);

    return "";
}

void
arm_me()
{
    object robe;

    clone_object(WEP_STAFF)->move(TO,1);
    command("wield all");
    clone_object(WOHS_GUILD_OBJECT)->move(TO, 1);
    robe = clone_object(WOHS_ROBE);
    robe->set_robe_colour("white");
    robe->move(TO, 1);
    clone_object(VEST)->move(TO,1);
    clone_object(BREECHES)->move(TO,1);
    clone_object(BELT)->move(TO,1);
    clone_object(HERB_POUCH)->move(TO,1);
    clone_object(SATCHEL)->move(TO,1);
    command("wear all");
    command("wear hood");
    command("tie pouch");
    command("tie satchel");
}

void
get_me_soul()
{
    add_cmdsoul(WOHS_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul(WOHS_SPELLS + "acid_arrow");
    update_hooks();
    remove_alarm(soul_id);
}

string
query_wohs_order_colour()
{
    return "white";
}

string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}

int
query_guild_level_occ()
{
    return 12;
}

public int
can_ignore_ingredients(object caster)
{
    return 1;
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

int
query_cantrip_spells_max()
{
    return 4;
}

int
query_minor_spells_max()
{
    return 4;
}

int
query_lesser_spells_max()
{
    return 4;
}

int
query_greater_spells_max()
{
    return 4;
}

int
query_advanced_spells_max()
{
    return 4;
}

void
prepare_reaction(object aspirant)
{

    string name = aspirant->query_real_name();

    if (!handle_timed_messages(aspirant)) {
        aspirant->catch_msg(C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
           "someone else. You should wait until he is finished.\n");
        return;
    }

    if(WOHS_MANAGER->query_player_started_wohs_test(aspirant) &&
      (WOHS_MANAGER->query_wohs_test_prop(aspirant, LEFT_TEST) < 2))
    {
        speak = ([
            1 : ({ 0.5, "smile solemnly " + name}),
            2 : ({ 0.5, "introduce myself"}),
            3 : ({ 0.5, "say Welcome back to the Hall of Mages, " +
                        C(name) + "." }),
            4 : ({ 1.0, "say You may continue your Test by entering the " +
                        "shadows again."}),
            5 : ({ 2.5, "stare intently at " + name}),
            6 : ({ 2.5, "say But be warned, if you return to the Void " +
                        "again before completing the Test, it will " +
                        "count as a failure."}),
            7 : ({ 4.0, "say And failure means death."}),
       ]);
    }
    else
    {
        speak = ([
            1 : ({ 0.5, "smile knowingly " + name}),
            2 : ({ 0.5, "introduce myself"}),
            3 : ({ 0.5, "say Welcome to the Hall of Mages, " +
                        C(name) + "." }),
            4 : ({ 1.0, "say So you have answered the summons of the " +
                        "Conclave, and wish to attempt the Test of High " +
                        "Sorcery?"}),
            5 : ({ 4.0, "stare intently at " + name}),
            6 : ({ 3.0, "say To begin the Test, all you need do is " +
                        "enter the shadows to your west."}),
            7 : ({ 3.0, "gesture west"}),
            8 : ({ 2.0, "say But I caution you, make sure you are " +
                        "completely prepared!"}),
            9 : ({ 2.0, "say Only the most capable of aspiring mages are " +
                        "permitted to take the Test, yet it is tailored " +
                        "to challenge you in many ways."}),
           10 : ({ 3.0, "say And the price of failure is death."}),
           11 : ({ 3.0, "say If you have any questions, you may ask " +
                        "them of me now."}),
           12 : ({ 1.5, "smile patient"}),
       ]);
    }

    handle_timed_messages(aspirant, speak);

    return;
}

void
congrat_reaction(object aspirant)
{

    string name = aspirant->query_real_name();

    if (!handle_timed_messages(aspirant)) {
        aspirant->catch_msg(C(COMPOSITE_LIVE(TO))+ " is currently conversing with " +
            "someone else. You should wait until he is finished.\n");
        return;
    }

        speak = ([
            1 : ({ 0.5, "congratulate " + name}),
            2 : ({ 1.5, "say Well done, " + C(name) + "! You have " +
                        "rightfully earnt your robe as a practitioner " +
                        "of High Sorcery!" }),
            3 : ({ 3.5, "say You may be tired from the rigours of the " +
                        "Test. You now have full access to the Tower " +
                        "of High Sorcery, and I suggest you make your " +
                        "way to the sixth floor where wizard sleeping " +
                        "quarters can be found."}),
            4 : ({ 7.0, "say No doubt you are keen to take advantage " +
                        "of the resources of the Tower..."  }),
            5 : ({ 6.0, "say On the sixth floor you can further " +
                        "progress your elemental and arcane training..."}),
            6 : ({ 6.0, "say ...and on the seventh floor you will find " +
                        "the Tower Library, one of the greatest " +
                        "libraries on Krynn, where you will find much " +
                        "lore and be able to research a range of rare " +
                        "spells."}),
            7 : ({ 7.0, "say I shall leave you to familiarise yourself " +
                        "with the Tower, but again I want to " +
                        "congratulate you on your achievement and " +
                        "welcome you as a Wizard of High Sorcery!"}),
            8 : ({ 5.0, "smile warmly"}),
            9 : ({ 2.0, "wfarewell " + name}),
         ]);

    handle_timed_messages(aspirant, speak);

    return;
}

void
init_living()
{

    if(WOHS_MANAGER->query_invited_wohs_test(TP) &&
       !TP->query_prop(INTRO_TO_ASPIRANT))
    {
       set_alarm(0.5, 0.0, &prepare_reaction(TP));
       TP->add_prop(INTRO_TO_ASPIRANT, 1);
    }

    if(TP->query_prop(FINISHED_TEST))
    {
       set_alarm(0.5, 0.0, &congrat_reaction(TP));
       TP->remove_prop(FINISHED_TEST);
    }
    else if(WOHS_IS_MEMBER(TP))
    {
       if(!handle_timed_messages(TP))
         return;

       string wohs_name = TP->query_real_name();
       set_alarm(0.5, 0.0, &command("smile acknowledg " + wohs_name));

       if(!TP->query_introduced("par-salian"))
          set_alarm(0.8, 0.0, &command("introduce myself to " + wohs_name));
    }

    ::init_living();
}
