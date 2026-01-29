#define RUN_Q_BIT 1
#define RUN_Q_GROUP 7
#define DID_RUN_QUEST() test_bit("Sparkle", RUN_Q_GROUP, RUN_Q_BIT)

#define QUEST_TOKEN "_bandit_quest_token"
#define QUEST_BURDEN "_bandit_quest_burden"
#define QUEST_FAMILY "_bandit_quest_family"
#define QUEST_RUNAWAY "_bandit_quest_runaway"

#define KIDNAP_IDENT    99286125
#define KIDNAP_RANGE    3
//Method names
#define K_CHOKE     0
#define K_KNOCK     1
#define K_PEAR      2

#define FAMILY_IDENT   495658643 /* the large number. */
#define FAMILY_RANGE   5         /* the number of relation options. */

#define REGRETS   73909412
#define DEAREST   10974220
#define HURT      20398156
#define ROLE_CANDIDATES  3


#define RUN_NAMES ({ "adien", "alvos", "antis", "arcion", "berus", "beswyn", \
    "brosk", "celtier", "clebo", "cletar", "codris", "drevan", \
    "ditriun", "drigus", "enko", "feros", "frelis", "frem", \
    "gerus", "gret", "gliff", "herum", "holten", "indel", \
    "jurg", "kep", "koltus", "lengar", "linten", "leppal", \
    "mardus", "medin", "mirat", "mulkeh", \
    "nilian", "odus", "pavir", "petor", "podra", "predigan", \
    "prufan", "quott", "roggus", "stelli", "sul", "talus", \
    "treman", "tilier", "trivor", "vantus", "velir", "witrun" })
#define RUN_IDENT   289500312
#define RUN_RANGE   51

#define REGRET_IDENT   82332005
#define REGRET_RANGE   6
/*Phrases and their match patterns are handled in shared_functions.c: */

#define HURT_IDENT   1953580
#define HURT_RANGE   6
/*Phrases and their match patterns are handled in shared_functions.c: */

#define TOKEN_NAMES ({ "spinning top", "charm bracelet", "forked stick", \
  "faded scarf", "cracked seashell", "straw doll" })
#define TOKEN_DESCS ({ "The point of this spinning top has dulled from "\
    + "frequent use. If placed correctly, it will remain upright "\
    + "indefinitely, but it "\
    + "will not be spinning while doing so. The string once used to set in it "\
    + "motion is worn to single threads in places.\n",\
    "The band of the bracelet is frayed to the "\
    + "point of breaking. Five glass beads hang from thick threads tied "\
    + "around the main band, interspersed with other threads that appear to "\
    + "have come undone or snapped.\n",\
    "The main length of this stick branches into two symmetric "\
    + "twigs separated by a 45-degree angle. It is too short to make a "\
    + "divining rod, and too thin to be any use as a slingshot. Still, "\
    + "the end has been worn smooth by frequent handling.\n",\
    "This wool scarf was woven out of dyed "\
    + "wool - blue, red and yellow. The overall colour is closer to brown "\
    + "thanks to long exposure to sunlight and a number of stains. Patching "\
    + "at the ends suggests it was worn many times.\n", \
    "This is one half of a bivalve seashell, "\
    + "brown and ridged on the outside. A crack runs halfway along the "\
    + "length of a ridge passing through the centre of the outside face. The "\
    + "species of shell is common, such as might be found along the coast "\
    + "near Sparkle.\n",\
    "A bundle of longer straw pieces was bent in half, the bend creating the "\
    + "head and the ends becoming legs. A shorter bundle was passed between "\
    + "the two bent parts and became arms. Bits of twine hold the figure "\
    + "together at the ankles, wrists, waist and neck. Dried stems, possibly "\
    + "the remains of small flowers are tied around the body of the doll.\n" })
#define TOKEN_IDENT   103968835 /* the large number. */
#define TOKEN_RANGE   5         /* the number of possible tokens. */
