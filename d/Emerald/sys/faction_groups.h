#ifndef EMERALD_FACTION_GROUPS_HEADER
#define EMERALD_FACTION_GROUPS_HEADER

#define FACTION_GROUPS ([ \
    "AvularCitizens" : ([ \
        "TelberinGuards"    : -100 , \
        "TelberinRoyalty"   : -150 , \
        "TelberinMerchants" : -50  ]), \
    "AvularMerchants" : ([ \
        "TelberinRoyalty"   : -50 ]), \
    "TelberinGuards" : ([ \
        "AvularCitizens"    : -100 ]), \
    "TelberinRoyalty" : ([ \
        "AvularCitizens"    : -100 , \
        "AvularMerchants"   : -50  ]), \
    "TelberinMerchants" : ([ \
        "AvularCitizens"    : -50  ]),\
    ])

#endif
