
/* 
   
  Automatic medieval-style insult generator, for use in Calian cmdsoul
  primarily.

  Coded by Maniac  27/4/95. 
  
  Thanks to Strider for suggesting the adjective triples, which are 
  from a widely distributed public domain medieval insult kit on 
  the Internet. I don't know the original author of those unfortunately.  
  But as they are so cool, and it further glorifies them to expand
  their usage, they're included here on Genesis.  

  The second sentence parts of the insults are by Maniac, except 
  for the yak one by Strider, the "rodent eyes and cauliflower ears"
  reference which was heard on a sports radio 5 show, along with
  the "how can he be that ugly with only one head?" question
  (in reference to Matthew LeTissier if I remember right), and 
  "if brains were sh*t you'd be constipated" is an insult from 
  English National Service days. 

  History:
      27/1/2001  moved to new dir              Maniac 
      19/10/98   Minor corrections             Maniac 
 
*/

inherit "/std/object";

string
*adj1 = ({"artless", "bawdy", "beslubbering", "bootless", "churlish", 
          "cockered", "clouted", "craven", "currish", "dankish", 
          "dissembling", "droning", "errant", "fawning", "fobbing",
          "froward", "frothy", "gleeking", "goatish", "gorbellied", 
          "impertinent", "infectious", "jarring", "loggerheaded", 
          "lumpish", "mammering", "mangled", "mewling", "paunchy", 
          "pribbling", "puking", "puny", "quailing", "rank", "reeky", 
          "roguish", "ruttish", "saucy", "spleeny", "spongy", "surly",
          "tottering", "unmuzzled", "vain", "venomed", "villainous",
          "warped", "wayward", "weedy", "yeasty" });

string
*adj2 = ({"base-court", "bat-fowling", "beef-witted", "beetle-headed", 
          "boil-brained", "clapper-clawed", "clay-brained", "common-kissing", 
          "crook-pated", "dismal-dreaming", "dizzy-eyed", "doghearted", 
          "dread-bolted", "earth-vexing", "fat-kidneyed", "fen-sucked", 
          "flap-mouthed", "fly-bitten", "folly-fallen", "fool-born", 
          "full-gorged", "guts-griping", "half-faced", "hasty-witted", 
          "hedge-born", "hell-hated", "idle-headed", "ill-breeding", 
          "ill-nurtured", "knotty-pated", "milk-livered", "motley-minded",
          "onion-eyed", "plume-plucked", "pottle-deep", "pox-marked", 
          "reeling-ripe", "rough-hewn", "rude-growing", "rump-fed", 
          "shard-borne", "sheep-biting", "spur-galled", "swag-bellied", 
          "tardy-gaited", "tickle-brained", "toad-spotted", "unchin-snouted", 
          "weather-bitten" });

string
*name = ({"apple-john", "baggage", "barnacle", "bladder", "boar-pig", 
          "bugbear", "bum-bailey", "canker-blossom", "clack-dish", 
          "clotpole", "coxcomb", "codpiece", "death-token", "dewberry", 
          "flap-dragon", "flax-wench", "flirt-gill", "foot-licker", 
          "fustilarian", "giglet", "gudgeon", "haggard", "harpy", 
          "hedge-pig", "horn-beast", "hugger-mugger", "jolthead", 
          "nut-hook", "pigeon-egg", "pignut", "puttock", "pumpion", 
          "ratsbane", "scut", "skainsmate", "strumpet", "varlot", 
          "vassal", "whey-face", "wagtail" });

mixed 
insults =  
      ({
          "I must avert my gaze from thy puss-ridden features for " +
            "fear of turning to stone!",
          "why wearest thou thy bum on thy shoulders for all to see?",
          "it puzzles me, how canst thou be that ugly with only one head?",
          "forsooth, I have heard of the face that launched a thousand " +
            "ships, yet now I see the one that sank them.",
          "thou art so ugly that thy rodent eyes and cauliflower ears " +
            "are thy best features.",
          "thou art a wart on a camel's backside.",
          "thou reekest like cow manure and stale wart-hog farts.",
          "away with thee, thy odour is like that of a skunk " +
            "with a digestive ailment.",
          "thy breath could drop a wild bull at a hundred paces.",
          "I beg of thee, depart and take the flies that follow thy " +
            "rotten stench with thee.",
          "I pray that there were a cess pit nearby to hide the stench " +
            "of thy armpits.",
          "thy skin is infested with countless lice and fleas.",
          "if brain were manure thou wouldst surely be constipated.",
          "thou hast all the wit of a kobold with a crossbow bolt " +
            "through both ears.",
          "thou hast the intelligence of a bisected amoeba.",
          "thy pitiful brain hath the circumference and density of an " +
            "undersized walnut.",
          "thou movest and fightest like a donkey.", 
          "thou hast the grace of a three-legged giraffe.",
          "thou art so clumsy that thou couldst not hit the " +
            "backside of a dragon with a halberd.",
          "thou art a bumbling oaf with the grace of a pregnant cow.",
          "thy gait hath all the style of a wounded hippopotomous.",
          "thou hast all the charm of a yak's stained codpiece.",  
          "thy unbelievably tiresome persona doth make me yawn.",
          "thou art such a bore, I yawn in thy face and struggle " +
            "to keep my eyelids up in thy presence.",
          "thy dreary manner maketh watching grass grow seem " +
            "interesting.",
          "what hath made thee so dull and soporific that even the " +
            "air around thee turns stale?" 
    });

int adj1_size = sizeof(adj1);
int adj2_size = sizeof(adj2);
int name_size = sizeof(name);
int insults_size = sizeof(insults);
int *insult_sequence;
int insult_count = -1;
int *static_sequence;


void
shuffle_sequence()
{
    int *tmp, i, j;

    insult_sequence = ({ });
    tmp = static_sequence;

    for (i = 0; i < insults_size; i++) {
        j = tmp[random(sizeof(tmp))];
        tmp -= ({j});
        insult_sequence += ({j}); 
    }
}


string
query_insult()
{
    int i;

    insult_count++; 
    if (insult_count >= insults_size)
        insult_count = 0;

    if (insult_count == 0)
        shuffle_sequence();

    return ("Thou " +
            adj1[random(adj1_size)] + " " +
            adj2[random(adj2_size)] + " " +
            name[random(name_size)] + ", " +
            insults[insult_sequence[insult_count]]);
}


void
create_object()
{
    int i;

    static_sequence = ({ });
    for (i = 0; i < insults_size; i++) 
        static_sequence += ({i});
}

