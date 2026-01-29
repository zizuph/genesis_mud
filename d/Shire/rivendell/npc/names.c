/*
 * Based on the hobbitmaker
 * by Finwe, December 1997
 * names used by elf npcs
 */

/* Prototypes */

string get_male_name();
string get_female_name();

#define MALENAME ({\
        "ameril", "amonduil", "analdur", "belolas", "caladrieriand", \
        "celadrielad" , "cilmamir", "delondel", "delorfinduil", "earilmawyn",\
        "earon", "earyndel", "elorfindel", "elvandel",\
        "filith", "fiondel", "fithralas", "fynduil", "galeldor",\
        "glithrawyn", "hadrieldor", "hilgandel", "isondil", "iselas",\
        "iseriand", "isithrarion", "lomandil", "membrilas", "mewyn",\
        "mithral", "nebrimbor", "niondil", "nyldor", "paldor",\
        "porfindil", "rebrindil", "relad", "selas", "silgaldor",\
        "silmalith", "tinandel",  "throndel", "throrfindel", "tinar",\
        "urondel", "vawyn", "violad", "vithralas", "voriand"})
// 49 Male Names :)


#define FEMALENAME ({\
        "amerith", "amunde", "anadrielia", "anethian", "anoniel",\
        "cade", "cadrielinde", "cilmande", "ciodien", "deleviel",\
        "delithraniel", "delorfiwiel", "earandriede", "earebriwiel", "elade",\
        "elaraclya", "elarania", "farwien", "fithralinde", "fiwien",\
        "galadrierith", "galaniel", "glithrathiel", "glorfiniel", "hiniel",\
        "isolia", "legadrielia", "legoniel", "melinde", "methiel",\
        "nilmathien", "nithronia",  "padrielinde", "rilmathiel", "sarawien",\
        "silmaviel", "tebrilinde", "thrilmalinde", "tinulia", "tinorfirith",\
        "unorfilia", "vadriede"})

// 42 Female names ;)

string
get_male_name()
{
   int ran;
   ran = random(49);
   return(MALENAME[ran]);
}

string
get_female_name()
{
   int ran;
   ran = random(42);
   return(FEMALENAME[ran]);
}
