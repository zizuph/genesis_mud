
/* 
     Kroug acts to occupational guild members. 
     Coded by Maniac for kroug brain. 

     History: 

     1996/1997/1998/1999/2000/2001  updates        Maniac 
     14/7/2001   changed to inheritable file       Maniac 
*/ 

#include <macros.h>
#include "defs.h"
#include CALIA_DOMAIN_DEFS
#include CALIA_FILE_DEFS
#include CALIA_KROUG_DEFS
#include CALIA_GUILD_RECORD_DEFS


mapping occ_mid = 
       ([ CALIAN : "Calian", 
          DRAGONARMY : "dragonarmy", 
          GLADIATOR : "gladiator", 
          MORGUL : "mage", 
          RANGER : "ranger",
          MONK : "monk", 
          KNIGHT : "knight", 
          SHADOW_UNION : "unionite", 
          NEIDAR : "neidar", ]); 

string *occ_head = ({ "goon", "nincompoop", "twit", "wooden-head", 
                      "wart-hog", "fish-spittle", "froth-dribbler", 
                      "nose-picker", "weed-eater", "grease-chewer" }); 


mapping occ_act_count = ([ ]); 
mapping occ_acts_left = ([ ]); 


/* 
 * Function:     set_occ_act_count
 * Description:  Set the number of acts for a particular guild. 
 * Arguments:    string guild_name - the guild name (query_guild_name_occ) 
 *               int act_count     - the number of acts for the guild 
 */ 
private void 
set_occ_act_count(string guild_name, int act_count) 
{ 
    occ_act_count[guild_name] = act_count; 
} 


/* 
 * Function:     reset_occ_acts 
 * Description:  Reset the occ guild acts for a particular guild. 
 *               This sets up a list of indices for the acts in an array, 
 *               which is identified by the guild name in the global mapping 
 *               occ_acts_left. 
 * Returns:      int * - the reset array of indices. 
 */ 
int * 
reset_occ_acts(string guild_name)
{
    int i, lim, *tmp; 

    lim = occ_act_count[guild_name]; 
    tmp = ({ }); 

    for (i = 0; i < lim; i++) 
        tmp += ({ i }); 

    return (occ_acts_left[guild_name] = tmp); 
}


/* 
 * Function:     next_random_occ_act_index 
 * Description:  Gets a random index for the remaining occ acts of 
 *               the named guild, and removes it. 
 * Returns:      the got index 
 */ 
int
next_random_occ_act_index(string guild_name)
{
    int *tmp, ix; 

    if (!(tmp = occ_acts_left[guild_name]) || 
        !sizeof(tmp)) 
    { 
        tmp = reset_occ_acts(guild_name); 
    }
 
    ix = tmp[random(sizeof(tmp))]; 
    occ_acts_left[guild_name] = tmp - ({ ix }); 

    return ix; 
}



/* 
 * Function:      init_occ_acts 
 * Description:   Initialises the number of occupational guild
 *                acts for each guild, and resets them. 
 */ 
void
init_occ_acts()
{
    set_occ_act_count(CALIAN, 18); 
    reset_occ_acts(CALIAN); 
    set_occ_act_count(GLADIATOR, 7); 
    reset_occ_acts(GLADIATOR); 
    set_occ_act_count(MORGUL, 8); 
    reset_occ_acts(MORGUL); 
    set_occ_act_count(RANGER, 8); 
    reset_occ_acts(RANGER); 
    set_occ_act_count(MONK, 8); 
    reset_occ_acts(MONK); 
    set_occ_act_count(KNIGHT, 8); 
    reset_occ_acts(KNIGHT); 
    set_occ_act_count(DRAGONARMY, 6); 
    reset_occ_acts(DRAGONARMY); 
    set_occ_act_count(SHADOW_UNION, 5); 
    reset_occ_acts(SHADOW_UNION); 
    set_occ_act_count(NEIDAR, 5); 
    reset_occ_acts(NEIDAR); 
}


string
query_random_guild_address(object player, string guild_name)
{
    if (!random(3)) 
        return ("Hey, " + occ_mid[guild_name] + ", "); 

    return (occ_mid[guild_name] + " " + 
            occ_head[random(sizeof(occ_head))] + ", ");  
}


string
query_occ_act(string guild_name, int index, object player)
{
    switch (guild_name)
    { 
        case CALIAN : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                     "we will see whose belief is stronger!"); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                     "one less of you wolfies would be nice, but " +
                     "that would still leave..  er..  a lot. Damn."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                     "here's method number 472 to kill Caliana: " +
                     "skewer her with a farmer's manure fork."); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "if we cooked Caliana in pastry would she " +
                    "still be a jammy tart?"); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "here's method number 116 to kill Caliana: " + 
                    "dice her with a meat cleaver and serve her up with a " + 
                    "helping of sprouts."); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "here's method number 724 to kill Caliana: " +
                    "strangulation with a gopheroo's intestines."); 
                case 6 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "here's method number 266 to kill Caliana: " +
                    "boil her in a vat of prune juice."); 
                case 7 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "here's method number 593 to kill Caliana: " +
                    "drop a statue of Hurn on her."); 
                case 8 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "it has to be said that Calians are " +
                    "total and utter FLUKERS. Too damn lucky by " +
                    "half, I mean."); 
                case 9 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "how dare you stand on our territory " +
                    "pretending you own it! Oh, you do, eh?"); 
                case 10 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "we're gonna knock down your sugar-frosted palace. " +
                    "Straight in there with the old heavy " +
                    "duty siege engine and *thump* *boing* *thwack*"); 
                case 11 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I hate wolves.. growl all the time, big " +
                    "fangs, and bad breath.. reminds me of my family."); 
                case 12 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "why do you guys fight so dirty, you " +
                    "trying to upstage us or what?"); 
                case 13 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you did not win the great battle, it was " + 
                    "a draw! We had to do a strategic withdrawal to check our " +
                    "inventories."); 
                case 14 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "we should wedge your medallions in your " +
                    "mouths, you'd make just as much sense but at least you'd " +
                    "be quieter."); 
                case 15 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I'd be obliged if you aim for my head when " +
                    "you swarm, it doesn't have any weak spots."); 
                case 16 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "stand still! It's not as if it was " + 
                    "easy to hit bleedin' Calians anyway."); 
                case 17 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "tell that Raspatoon I still want my " + 
                    "organs back, if he thinks he can just forget about it " + 
                    "after twenty years he's mistaken."); 
            } 
            break; 

        case GLADIATOR : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "we have an arena of our own you " +
                    "know, our contests tend to feature one unarmed " +
                    "Calian versus a minotaur and a black dragon."); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I think your axe skill has " +
                    "almost reached the level necessary to hit a tree, " +
                    "congratulations."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "that Kalak is a brutal bugger, I like him."); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "don't charge me, I hate being winded!"); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "whatever you do, don't go berserk, " +
                    "all that heavy breathing really puts me off."); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "so what's it like being a slave? " +
                    "Whoops, I should know."); 
                case 6 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "that Athasian sun obviously shrivelled " + 
                    "your brain to garden pea proportions."); 
            } 
            break; 

        case MORGUL : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "leave off the black magic, I've had my fill of that!"); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "pllleeeaaaase, anything but the high pitched whining!"); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you creatures are way too creepy, get outa here!"); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "go and cook a dunadan, I know for a fact " +
                    "I will taste horrible."); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "there's a faintly putrid smell around here.. but " +
                    "it's only faint.. had a wash recently eh?"); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I've never trusted anyone with glow-in-the-dark eyes."); 
                case 6 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "a lidless eye is much easier to poke, mark my words!"); 
                case 7 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I'll wager we're more sophisticated at torture than " +
                    "you, we have custom made codling grinders."); 
            } 
            break; 

        case RANGER : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "why aren't you hiding in the bushes?");  
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I hear the ringwraiths have some interesting " +
                    "decor planned for Minas Tirith."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "who in their right mind would protect those " +
                    "batty Shirelings anyway?"); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you can stick your herbs up your.. er, nose!"); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "pity about that Numenor eh.. I mean that " +
                    "some of you actually survived."); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "don't you dare throw sand in my eyes, this " + 
                    "isn't a beach!"); 
                case 6 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you're only here 'cos it's the furthest " +
                    "you could get from the Gondor front line!"); 
                case 7 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I hear herbs and stewed dunadan are really " +
                    "big in Morgul this time of year."); 
            } 
            break; 

        case MONK : 
            switch (index) 
            { 
               case 0 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "how appropriate, a ruined monk for a " +
                   "soon-to-be-ruined monastery!"); 
               case 1 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "religion is dangerous in the wrong fists!"); 
               case 2 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "the way your fighting style mimics a dragon " +
                   "hatchling scrambling its way out of an egg does your " +
                   "Order's name credit!"); 
               case 3 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "if you had a halo I'd strangle you with it!"); 
               case 4 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "is it true you used to shave your heads so the " +
                   "lice would lead a more frugal life?"); 
               case 5 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "prepare to have an out of body experience!"); 
               case 6 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "don't kick me, I'm not wearing a sign on my back!"); 
               case 7 : return 
                   ("say " + query_random_guild_address(player, guild_name) + 
                   "do you abstain from the pleasures of the flesh? " + 
                   "I find flesh can be great fun, provided I'm cutting " + 
                   "it off someone that is."); 
            } 
            break; 

        case KNIGHT : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "learn to fight dirty, you get " +
                    "to kick people in the figgin."); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I've always wondered how one can " + 
                    "honourably beat the living daylights out of someone."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "do you have a pure heart? I collect " + 
                    "them in pickle jars."); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "may draconians roast the buttocks of " + 
                    "your family over a log fire!"); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "show me an effigy of Paladine and chop " +
                    "it up into small pieces and play marbles with them."); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "the only `measure' you need is the size " + 
                    "of your coffin."); 
                case 6 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I'll take an oath of my own: I swear " + 
                    "I'll shove my weapon through your ears!"); 
                case 7 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you must get so bored trying to be virtuous, " + 
                    "try being a bastard, it's much more fun!"); 
            } 
            break; 

        case DRAGONARMY : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "go and smash up that palace for us, it's fun!"); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "these spaces are reserved for our siege " +
                    "engines, if you park your dragon we'll have it " +
                    "towed away."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "if you steer your dragon like you fight we'd " +
                    "better get the hell out of here next time you land!"); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "knights are pompous asses, the dragonarmies " +
                    "just forewent the complexity of being pompous!"); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I heard you were so drunk once you tried " +
                    "to mount an irate Draconian by mistake and that's " +
                    "how you came to lose some of your most important " +
                    "apparatus."); 
                case 5 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "so, managed to wipe out more of that knight " +
                    "filth lately?"); 
            } 
            break; 

        case SHADOW_UNION : 
            switch (index) 
            { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "one of these days we'll load you in a " + 
                    "catapult and give you a projectile view " + 
                    "of the palace."); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I never cry when I chop up a shadow onion."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "your speed is legendary! There are " +
                    "countless tales of your almost instantaneous " +
                    "disappearance over the horizon from your enemies.");  
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I need to borrow a combat veil, I think I'm " + 
                    "going to sneeze."); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "shadow boxing has never been this much fun!"); 
            } 
            break; 

        case NEIDAR : 
           switch (index) 
           { 
                case 0 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "ack! I'm being savaged by a vicious overgrown " + 
                    "beard with a pair of feet protruding at the base!"); 
                case 1 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you'd look far better decorating the bottom of " + 
                    "a mine shaft."); 
                case 2 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "you aren't ready for this, go back to cutting " + 
                    "twigs and knocking out grasshoppers!"); 
                case 3 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "I hear you infiltrated the giants' headquarters " + 
                    "by hiding under one of their bootstraps."); 
                case 4 : return 
                    ("say " + query_random_guild_address(player, guild_name) + 
                    "watch out for the avian wildlife around here " + 
                    "there's a perfect nesting opportunity on your chin.");
            } 
            break; 
        default : 
            return ""; 
            break;       
    } 
    return ""; 
}



/* Kroug comments on the guild of a player */
void
guild_comment(object kroug, object player)
{
    string guild; 

    if ((!objectp(kroug)) || (!objectp(player)))
        return;

    if (!stringp(guild = player->query_guild_name_occ()) || 
        !strlen(guild) || !occ_act_count[guild] || 
        player->query_incognito_occ(kroug))
        return;

    kroug->command(query_occ_act(guild, 
                                 next_random_occ_act_index(guild), 
                                 player)); 
}

