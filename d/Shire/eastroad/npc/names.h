
//names.h by Dunstable, February 26, 1995
// used for giving the hobbit master files
// a bit more flavor
/* Prototypes */

string get_family_name();
string get_male_name();
string get_female_name();

#define MALENAME ({\
                     "adalgrim","adelard","andwise","anson",\
                     "balbo","bandobras","berilac","bilbo",\
                     "bingo","blanco","bodo","bowman",\
                     "bucca","bungo","carl","dinodas",\
                     "doderic","dodinas","drogo","dudo",\
                     "falco","fastolph","ferumbras","filibert",\
                     "flambard","folco","fortinbras","fosco",\
                     "fredregar","gerontius","gorbadoc","gormadoc",\
                     "griffo","halfred","hamfast","hamson",\
                     "hildafons","hildigrim","hob","hobson",\
                     "holfast","holman","hugo","ilberic",\
                     "isembold","isengar","isengrim","isumbras",\
                     "largo","lotho","madoc","marcho",\
                     "marmadoc","meriadoc","milo","minto",\
                     "mungo","odo","odovacar","orgulas",\
                     "otho","paladin","peregrin","polo",\
                     "ponto","posco","robin","rudigar",\
                     "sadoc","samwise","sancho","saradoc",\
                     "tobold","togo","tolman","wilibard",\
                     "wiseman"})

// 77 Male Names :)


#define FEMALENAME ({\
                    "adaldrida","adamanta","amaranth","angelica",\
                    "bell","belladonna","berylla","camellia",\
                    "celandine","chica","daisy","diamond",\
                    "dora","elanor","esmeralda","estella",\
                    "gilly","hilda","hildagard","lily",\
                    "linda","lobelia","malva","menegilda",\
                    "mentha","pansy","pearl","peony",\
                    "pervinca","poppy","primrose","primula",\
                    "prisca","rosa","rosamunda","rose",\
                    "ruby","salvia","tanta"})

// 39 Female names ;)

#define FAMILYNAME ({\
                    "Cotton","Bolger","Bunce","Brandybuck",\
                    "Took","Baggins","Gamgee","Oldbuck",\
                    "Underhill","Boffin","Chubb","Grubb",\
                    "Bracegirdle","Goodbody","Hornblower","Proudfoot",\
                    "Twofoot","Whitfoot","Tunnely","Smallburrows",\
                    "Gammidge","Roper","Maggot","Hogg",\
                    "Sackville-Baggins","Chubb-Baggins","Brown","Brockhouse",\
                    "Sandheaver","Sandyman"})

//30 family names


string
get_family_name()
{
   int ran;
   ran = random(30);
   return(FAMILYNAME[ran]);
}

string
get_male_name()
{
   int ran;
   ran = random(77);
   return(MALENAME[ran]);
}

string
get_female_name()
{
   int ran;
   ran = random(39);
   return(FEMALENAME[ran]);
}
