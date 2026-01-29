/*
 * Copyright (C) 07-December-2000 by Shadow deForest.
 *
 * Creator  : Shadowlynx
 * Date     : 07-December-2000
 * Filename : adv_guild.c
 * Purpose  : This is the Adventurer Guild for Sparkle.
 * Credits  : Modified from the original file of
 *              1. </d/Genesis/start/human/town/adv_guild.c>
 *                 by Styles - January, 1992.
 * Includes : Meditation.
 *            Set preferences.
 *            List guilds.
 *            Train general skills.
 *            Self restriction.
 *            Charity box.
 * Updates  : 13-December-2000 by Shadowlynx
 *              - The charity box was modified to allow wanderer level
 *                or less to take items from the box. If an item is
 *                donated by mistake or the person changes their mind,
 *                the item may be retrieved by the one who donated it
 *                despite their level. Any item placed in the charity
 *                box cannot be sold except during Armageddon, excluding
 *                retrieved items. A player is allowed to take one weapon
 *                or armour type from the box. A check is made against the
 *                players inventory if they attempt to take a second one
 *                of the same type and the attempt will be unsuccessful.
 *                This is to promote donations to the box and use of the
 *                items rather than constant looting of the box to sell
 *                donated items for cash.
 *
 *          : 26-December-2000 by Shadowlynx
 *              - Detailed individual descriptions were added for all
 *                thirteen trophies.
 *          : 12-July-2002 by Morrigan
 *              - Added a mercenary poster to the room
 */

#pragma save_binary
#pragma strict_types

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

/* Prototypes */
void set_up_skills();
void reset_room();

/* variables */
object box, poster;

void
create_room()
{
    set_short("Sparkle Adventurer Guild");
    set_long("Welcome to the Sparkle Adventurer Guild.\n\n" +
      "Soft shadows flicker along the walls in the wavering" +
      " light of four blazing torches, one in each corner of the" +
      " room. Ornate wall sconces carved to look like dragon" +
      " claws hold each torch firmly in place. A number of" +
      " trophies adorn the walls which have been brought back" +
      " to the guild hall by bold adventurers. An age-worn" +
      " hardwood floor is mostly covered by a soft plush carpet" +
      " where many adventurers often sit down and relax.\n\n" +
      "Here an adventurer may advance their skills or set" +
      " personal priorities. You can choose to <meditate> and" +
      " reset your preferences. Additionally, you can <learn>" +
      " new skills or <improve> the ones you already have. With" +
      " <list guilds> you can find out information about the" +
      " guilds you are a member of.\n");

    add_item(({"box","charity box"}),"Donations of excess equipment or" +
      " items may be placed into this box for lesser experienced" +
      " adventurers to use if they have need.\n");
    add_item(({"shadows","soft shadows"}),"Faint outlines almost like" +
      " wisps of dark smoke flicker along the walls lending images" +
      " to the imagination like clouds in the sky.\n");
    add_item(({"light","wavering light"}),"Four blazing torches in" +
      " each corner of the room cast a soft, subdued wavering light" +
      " around the room.\n");
    add_item(({"torch","torches","blazing torch","blazing torches"}),
      "In each corner of the room is a blazing torch held firmly in" +
      " place by an ornate wall sconce carved to imitate the claws" +
      " of a dragon.\n");
    add_item(({"sconce","sconces","ornate sconce","ornate sconces"}),
      "Intricately carved sconces are attached to the walls in each" +
      " corner of the guild hall. They are designed to appear like" +
      " the claws of a dragon. A blazing torch rests firmly in each" +
      " set of claws.\n");
    add_item(({"wall","walls"}),"Several trophies adorn the walls of" +
      " the guild hall. Most have been stuffed or mounted and depict" +
      " either animals or exotic creatures which may be found within" +
      " the realms.\n");
    add_item(({"trophy","animal","creature","exotic creature"}),"There" +
      " are so many to choose from, you can't decide which one to" +
      " look at first. Perhaps you could be more specific?\n");
    add_item(({"trophies","animals","creatures","exotic creatures"}),
      "Numerous trophies decorate the walls displaying the bravery" +
      " of past adventurers. Among these trophies, you spot a black" +
      " lion perched on a large rock surveying the surroundings, a" +
      " wild boar head with huge pointed tusks and a mean looking" +
      " snout, the preserved body of a death spider spinning a silky" +
      " cocoon around its victim, the head of a ferocious red dragon" +
      " with its open mouth ready to shoot a ray of burning flames," +
      " a bestial statue of a gargoyle squatting in stony silence," +
      " the head of a frost giant with a vicious snarl on its face," +
      " the fearsome heads of a magnificent hydra all swerving to" +
      " strike at an invisible target, the body of a giant shadow" +
      " lizard stalking its prey, the stone head of a medusa with" +
      " its hair a mass of wriggling snakes, the massive head of a" +
      " minotaur supporting a full set of horns, the body of a" +
      " giant octopus with each of its eight tentacles creeping along" +
      " the floor seeking a quarry, the graceful body of a snow wolf" +
      " scanning the area for its next kill, the coiled body of a wyrm" +
      " with its wings outstretched, and the unmistakable form of a" +
      " dogcow staring at you with sweet innocent eyes.\n");
    add_item(({"lion","black lion","lion perched on a rock",
        "lion perched on a large rock","rock","large rock",
        "black lion perched on a large rock",
        "black lion perched on a rock"}),
      "In one corner of the room underneath a blazing torch" +
      " a sleek black lion is perched on a large rock. Its" +
      " shiny dark eyes gaze intently at the surroundings." +
      " A bushy black mane creates a dark halo around its" +
      " head. Its regal and majestic stature also suggests" +
      " a cunning yet furtive grace. It is not known whether" +
      " black lions are the result of wizard experiments or" +
      " natural cross-breeding in the wild. What is certain," +
      " is that they are a cross between a black panther and" +
      " a lion, a mix that makes them the most savage of all" +
      " the hunting cats. Black lions are among the most deadly" +
      " of predators.\n");
    add_item(({"boar","wild boar","boar head","wild boar head",
        "tusks","pointed tusks","huge pointed tusks","snout",
        "mean snout","mean looking snout","huge tusks"}),
      "This is the head of a wild boar. Huge pointed tusks" +
      " protrude from under a mean looking snout. Wild boars" +
      " are hunted for their choice meat and pelts which can" +
      " fetch a small fortune in gold. They look like huge pigs" +
      " covered in tangled clumps of coarse reddish-brown hair." +
      " They are brutish, aggressive beasts and will stand and" +
      " fight with their tusks in an almost savage fury.\n");
    add_item(({"spider","death spider","preserved death spider",
        "preserved spider","body of a spider","preserved body",
        "body of a death spider","preserved body of a spider",
        "preserved body of a death spider","preserved body",
        "cocoon","silky cocoon","victim"}),
      "In one shadowy corner, near the top where the walls" +
      " intersect with the ceiling, is an intricate silky" +
      " spider web. In the center of this maze of sparkling" +
      " strands sits the preserved body of a death spider" +
      " looming over its paralyzed victim. The death spider" +
      " seems to be spinning a silky, snow-white coccoon" +
      " around its prey which shimmers in the flickering" +
      " torchlight. The death spider is a most deadly foe." +
      " These diabolical creatures appear as massive blue-black" +
      " spiders with splashes of burnt orange interspersed" +
      " along their stocky bodies and sharply jointed legs." +
      " The texture of their skin is a mass of short straight" +
      " hairs which make them look fuzzy. These death spiders" +
      " have demonic heads with sharp venomous fangs with" +
      " which they use to inject deadly paralyzing poisons" +
      " into their victims. Being almost a meter in size, they" +
      " lurk in dungeons and ruins ready to trap an unwary" +
      " adventurer.\n");
    add_item(({"dragon","red dragon","ferocious red dragon",
        "ferocious dragon","dragon head","red dragon head",
        "ferocious dragon head","ferocious red dragon head",
        "head of a ferocious dragon","head of a red dragon",
        "head of a ferocious red dragon","head of a dragon",
        "mouth","open mouth",}),
      "Mounted prominantly in the center of the south wall" +
      " sits the head of a ferocious red dragon. The mouth" +
      " of the dragon head is stretched wide open revealing" +
      " rows of sharp teeth gleaming in the flickering light." +
      " The nostrils are wide and flaring and almost pulse" +
      " with intensity. It looks ready to summon forth a" +
      " fiery ray of burning flames to scorch anyone who" +
      " comes into range. Red dragons are treasure hoarders" +
      " who relish collecting coins, jewels and other wealth." +
      " When encountered, a red dragon will usually be in a" +
      " cavern sprawled across the top of a huge pile of" +
      " valuables. Red dragons are automatically suspicious" +
      " of anyone they meet, believing them to be thieves" +
      " intent on stealing their treasure, therefore will" +
      " attack immediately. With nostrils flaring, they can" +
      " shoot fiery rays of burning flames from their mouths," +
      " which they send roaring through the air to explode" +
      " upon their victim.\n");
    add_item(({"statue","gargoyle statue","bestial gargoyle",
        "bestial gargoyle statue","gargoyle","bestial statue",
        "statue of a gargoyle","bestial statue of a gargoyle",
        "statue of a bestial gargoyle","squatting bestial statue",
        "squatting gargoyle","squatting bestial gargoyle",
        "squatting statue","squatting bestial gargoyle statue"}),
      "Nestled into another corner sits a bestial statue of" +
      " a gargoyle squatting in stony silence. Gargoyles are" +
      " ferocious beasts whose ability to blend with the" +
      " surrounding rock is such that they will surprise" +
      " a prey almost every time and be able to deliver" +
      " the first blow automatically. They are roughly" +
      " humanoid in shape, with clawed hands and feet," +
      " and bestial heads brimming with teeth and horns." +
      " A pair of large leathery wings sprout from their" +
      " backs, and a point-tipped tail hangs behind. They" +
      " are coloured a mottled grey that looks just like" +
      " stone. This camouflage allows them to play their" +
      " favorite trick on unsuspecting adventurers. This" +
      " being to stand motionless on a piece of stone and" +
      " pretend to be a statue until they can strike.\n");
    add_item(({"giant","frost giant","frost giant head",
        "giant head","head of a frost giant","snarl",
        "vicious snarl","head of a giant"}),
      "Centered on the west wall is the head of a frost" +
      " giant with a vicious snarl on its face. Frost" +
      " giants can range up to six meters tall and live" +
      " in the coldest regions. Their skin is pale white," +
      " but much of it is usually hidden by their long" +
      " white beards and hair, and under swathes of" +
      " polar bear fur. Frost giants are not afraid" +
      " of attacking adventurers, for they know that" +
      " gold may often be found in their pockets. Frost" +
      " giants dearly love to hoard their treasure in" +
      " caves.\n");
    add_item(({"hydra","fearsome hydra","magnificent hydra",
        "heads of a hydra","hydra heads","fearsome heads",
        "fearsome hydra heads","heads","swerving heads",
        "heads of a fearsome hydra","swerving hydra heads"}),
      "The entire east wall is dominated by the fearsome" +
      " heads of a magnificent hydra, each connected to" +
      " a long graceful neck sprouting from the center of" +
      " the wall, all sinuously swerving to strike at an" +
      " invisible target. This magnificent hydra is a" +
      " many-headed creature which can be found in many" +
      " different areas. Though they are quite rare, they" +
      " often figure as the villains in heroic tales. They" +
      " are reptilian creatures, like fat-bodied snakes," +
      " with a number of large heads rising on long necks" +
      " from their bodies. The beast can have as little as" +
      " two or as many as seven wide-mouthed, fang-filled" +
      " heads. Covered in metallic greenish-brown scales," +
      " this nightmarish beast can grow as much as ten" +
      " meters long.\n");
    add_item(({"lizard","shadow lizard","giant shadow lizard",
        "giant lizard","lizard body","giant shadow lizard body",
        "giant lizard body","body of a giant shadow lizard",
        "body of a giant lizard","body of a shadow lizard",
        "stalking giant shadow lizard","stalking lizard",
        "stalking shadow lizard"}),
      "Near the back of the room, nearly hidden within the" +
      " shadows is the replica of a giant shadow lizard" +
      " stalking its prey. Giant shadow lizards can be" +
      " major hazards to adventurers. They can be as" +
      " large as six meters tall and a half meter wide." +
      " The creatures appear slow as they lumber along" +
      " on four ungainly feet and drag their cumbersome" +
      " tails behind them, but in a fight they prove" +
      " to be remarkably agile, darting between swords" +
      " to deliver savage bites with their large fang" +
      " filled mouths.\n");
    add_item(({"medusa","medusa head","stone head",
        "stone medusa","stone head of a medusa",
        "hair","snakes","mass of wriggling snakes",
        "wriggling snakes","head of a medusa"}),
      "Above the archway to the north exit is mounted" +
      " the stone head of a Medusa with its hair a mass" +
      " of wriggling snakes. The Medusa is a strange" +
      " humanoid that looks like a wizened old lady" +
      " dressed in ragged clothes with her head covered" +
      " by a thick shawl. She appears harmless and" +
      " frail. Many adventurers have been taken in" +
      " by this helpless appearance and drawing near" +
      " to her have offered to help by lending a" +
      " strong arm to steady the poor old crone." +
      " With a demonic laugh, the Medusa will throw" +
      " back the shawl and fix the unwary traveller" +
      " with a red-eyed stare which has the power to" +
      " paralyze the victim. In place of the Medusa's" +
      " hair sprouts a mass of wriggling snakes. If" +
      " you stare too long at a Medusa, your limbs" +
      " will begin to stiffen and within moments" +
      " you will be nothing but solid stone!\n");
    add_item(({"minotaur","massive head of a minotaur",
        "minotaur head","massive head","horns"}),
      "Next to the doorway on the left side of the north" +
      " wall, the massive head of a minotaur is mounted." +
      " This beastly head supports a full set of deadly," +
      " sharply pointed horns. This perilous beast is" +
      " half-man, half-bull making for a fearsome" +
      " combination. The head is shaggy and bovine, with" +
      " a large pair of horns curving from the top. The" +
      " favorite method of attack from a minotaur is a" +
      " head-down charge, snorting and stamping just like" +
      " a bull.\n");
    add_item(({"octopus","giant octopus","octopus body",
        "giant octopus body","body of a giant octopus",
        "body of an octopus","creeping tentacles",
        "tentacles","eight tentacles"}),
      "Along the back wall is the body of a giant" +
      " octopus with each of its eight tentacles" +
      " creeping along the floor seeking a quarry." +
      " The giant octopus is a cunning predator," +
      " with a strong dextrous body. They can grow" +
      " to alarming sizes. Their favorite tactic is to" +
      " grasp a living creature, gradually enfolding" +
      " it in their tentacles and crushing the life" +
      " out of it.\n");
    add_item(({"wolf","snow wolf","snow wolf body",
        "wolf body","body of a wolf","graceful body",
        "body of a snow wolf","graceful body of a wolf",
        "graceful body of a snow wolf"}),
      "Poised against the eastern wall is the graceful" +
      " body of a snow wolf scanning the area for its" +
      " next kill. Snow wolves are larger than normal" +
      " wolves and are savage killers which fear nothing." +
      " They are covered all over with shaggy white fur," +
      " and blend well into their surroundings. Only their" +
      " hunger-glazed red eyes will give them away. Fire" +
      " will keep the snow wolf at bay, but wood burns" +
      " quicker than their patience slackens. The moment" +
      " the fire begins to die they will close in for" +
      " the kill.\n");
    add_item(({"wyrm","coiled wyrm","coiled wyrm body",
        "wyrm body","coiled body of a wyrm","coiled body",
        "outstretched wings","body of a coiled wyrm",
        "wings"}),
      "In a far corner sits the coiled body of a wyrm" +
      " with its leathery wings outstretched for balance." +
      " Wyrms are solitary beasts thought to be related" +
      " to dragons. They have lizard-like heads and" +
      " leathery wings. They live to a great age and" +
      " are highly intelligent. Wyrms are thin and" +
      " snake-like, without legs or feet and they" +
      " cannot fly. These great white beasts dwell" +
      " in icy regions where their colouring allows" +
      " them to blend with their background. Their" +
      " usual method of attack is to rear up on their" +
      " coils, wings outstretched for balance, and" +
      " blast their victims with their icy breath." +
      " They can also bite their victim but prefer to" +
      " use their breath weapon as much as possible.\n");
    add_item(({"dogcow","unmistakable head of a dogcow",
        "unmistakable dogcow head","head of a dogcow",
        "head of an unmistakable dogcow","innocent eyes",
        "sweet innocent eyes","sweet eyes","eyes"}),
      "Mounted on the right side of the north wall next"+
      " to the doorway is the unmistakable head of a" +
      " dogcow staring at you with sweet innocent eyes." +
      " This dogcow is a rather strange creature. It" +
      " looks somewhat like a very small cow, or perhaps" +
      " a very large terrier. It is covered with long" +
      " white hair with large patches of carbon black" +
      " mixed in. A pair of bone-yellow horns sprout" +
      " from the top of the head and are sharpened to" +
      " a gleaming point. It has deep soulful eyes but" +
      " doesn't appear dangerous. However, many an" +
      " adventurer has fallen victim to its beguiling" +
      " song of Moof!\n");
    add_item(({"carpet","plush carpet","soft carpet",
        "soft plush carpet"}),"A soft plush carpet covers most of the" +
      " age-worn hardwood floor. It looks very comfortable to rest on." +
      " Most people tend to sit down and meditate in the soft luxery" +
      " of this soft carpet.\n");
    add_item(({"floor","flooring","hardwood floor","hardwood flooring",
        "age-worn floor","age-worn flooring","age-worn hardwood floor",
        "age-worn hardwood flooring"}),"Beneath the soft plush carpet" +
      " is an age-worn hardwood floor. Several spots are scuffmarked" +
      " by the heavy treads of countless visitors to the guild hall.\n");

    add_exit("road3","north",0,0,0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    setuid (); seteuid (getuid ());
    box = clone_object(S_COMMON_OBJ_DIR + "charity_box");
    box->set_long("This is a large box where donations of excess" +
      " equipment or items may be placed for lesser experienced" +
      " adventurers to use. If you donate an item by mistake, it may" +
      " be retrieved if you change your mind.\n\n");
    box->move(this_object());

    reset_room();

    create_skill_raise();
    set_up_skills();
}

void
reset_room()
{
    int i;

    if (!poster)
    {
        setuid (); seteuid (getuid ());
        poster = clone_object(S_LINK_MERC_POSTER);
        poster->move(this_object());
    }

    if (!box || present("dagger", box))
        return;

    for(i = 0; i < 4; i++)
        clone_object(S_COMMON_WEP_DIR + "dagger")->move(box);
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),     0, 0, 30 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 30 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),       0, 0, 30 );
    me = "use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }),    0, 0, 20 );
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 30 );
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,	({ me, ot }), 0, 0, 30 );
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,  ({ me, ot }), 0, 0, 30 );
    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB, ({ me, ot }), 0, 0, 30 );
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,	({ me, ot }), 0, 0, 30 );
    me = "be aware of your surroundings"; ot = "be aware";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 30 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,	({ me, ot }),       0, 0, 30 );
    me = "ride a horse"; ot = me;
    sk_add_train(SS_RIDING,       ({ me, ot }),       0, 0, 30 );
}

void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();
}

