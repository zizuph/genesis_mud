/*
 *  genus.c
 *
 *  Beast Tamers genus.
 *
 *  Created by Carnak, December 2016
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include <macros.h>
#include <ss_types.h>

#include "../defs.h"


#define ARANEAE     ([  "araneae"       : ({                                   \
                        "hatchling",                                           \
                        "arachnid",                                            \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :   ({}),                                          \
        "AlpineTundra"      :   ({}),                                          \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        ([]),                                                  \
                        ([]),                                                  \
                        ({ 110, 160, 110, 60, 60, 100 }),                      \
                        (["left hindleg":({ 100, 10 }),                        \
                          "right hindleg":({ 100, 10 }),                       \
                          "left middle legs":({100, 10}),                      \
                          "right middle legs":({100, 10}),                     \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "chitin":({100, 20}),                                \
                          "head":({85, 15}),                                   \
                          "back":({65, 5})                                     \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"bites"}),                             \
                                "loc":({"pincers"})                            \
                            ]),                                                \
                          "slash":([]),                                        \
                          "bludgeon":([                                        \
                                "hit":({"thrusts at"}),                        \
                                "loc":({"left foreleg", "right foreleg"})      \
                            ]),                                                \
                        ]),                                                    \
                        ([ SS_PARRY : 5, SS_CLIMB : 5 ]),                      \
                        ([                                                     \
    SS_SNEAK          : ({ SS_SNEAK,          "sneaking",          50,  25 }), \
    SS_HIDE           : ({ SS_HIDE,           "hiding",            50,  25 }), \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "Patron of Arachnids", "Matron of Arachnids" }),    \
                        ({}),                                                  \
                        ({}),                                                  \
                        })                                                     \
                    ])

#define AMPHIBIA    ([  "amphibia"      : ({                                   \
                        "hatchling",                                           \
                        "amphibian",                                           \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :   ({}),                                          \
        "AlpineTundra"      :   ({}),                                          \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        ([]),                                                  \
                        ([]),                                                  \
                        ({ 120, 130, 130, 60, 60, 100 }),                      \
                        (["left hindleg":({100, 10}),                          \
                          "right hindleg":({100, 10}),                         \
                          "left foreleg":({100, 15}),                          \
                          "right foreleg":({100, 15}),                         \
                          "body":({100, 20}),                                  \
                          "head":({95, 20}),                                   \
                          "back":({70, 10}),                                   \
                          ]),                                                  \
                        (["impale":([]),                                       \
                          "slash":([]),                                        \
                          "bludgeon":([                                        \
                                "hit":({"attacks"}),                           \
                                "loc":({"left webbed-foot",                    \
                                        "right webbed-foot"}),                 \
                            ]),                                                \
                        ]),                                                    \
                        ([ SS_SWIM : 15 ]),                                    \
                        ([                                                     \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "", "" }),                                          \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])
                    
#define CANIDAE     ([  "canidae"       : ({                                   \
                        "pup",                                                 \
                        "canine",                                              \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :   ({"arctic wolf", "arctic fox"}),               \
        "AlpineTundra"      :   ({"coyote"}),                                  \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        (["ArcticTundra":({ ({"color"}), ({"pattern"}) })]),   \
                        ([]),                                                  \
                        ({ 130, 140, 100, 60, 60, 110 }),                      \
                        (["left hindleg":({85, 7}),                            \
                          "right hindleg":({85, 7}),                           \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          "tail":({65, 6})                                     \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"bites"}),                             \
                                "loc":({"maw"}),                               \
                            ]),                                                \
                          "slash":([                                           \
                                "hit":({"swipes"}),                            \
                                "loc":({"left paw", "right paw"}),             \
                            ]),                                                \
                          "bludgeon":([])                                      \
                        ]),                                                    \
                        ([ SS_TRACKING : 15 ]),                                \
                        ([                                                     \
    SS_SNEAK          : ({ SS_SNEAK,          "sneaking",          50,  25 }), \
    SS_HIDE           : ({ SS_HIDE,           "hiding",            50,  25 }), \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "Leader of the Pack", "Leader of the Pack" }),      \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])
                    
#define CERVIDAE    ([  "cervidae"      : ({                                   \
                        "calf",                                                \
                        "cervine",                                             \
                        "herbivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :   ({"caribou", "moose"}),                        \
        "AlpineTundra"      :   ({"elk", "mule deer"}),                        \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        (["ArcticTundra":({ ({"color"}), ({"pattern"}) })]),   \
                        ([]),                                                  \
                        ({ 130, 130, 120, 60, 60, 100 }),                      \
                        (["left hindleg":({85, 7}),                            \
                          "right hindleg":({85, 7}),                           \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          "backside":({65, 6})                                 \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"thrusts at"}),                        \
                                "loc":({"horns"}),                             \
                            ]),                                                \
                          "slash":([                                           \
                                "hit":({"attacks"}),                           \
                                "loc":({"left fronthoof", "right fronthoof"}), \
                            ]),                                                \
                          "bludgeon":([])                                      \
                        ]),                                                    \
                        ([ SS_HERBALISM : 15 ]),                               \
                        ([                                                     \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "", "" }),                                          \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])

#define FELIDAE     ([  "felidae"       : ({                                   \
                        "kitten",                                              \
                        "feline",                                              \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :  ({"snow leopard"}),                             \
        "AlpineTundra"      :  ({"bobcat", "mountain lion"}),                  \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        (["ArcticTundra":({ ({"color"}), ({"pattern"}) })]),   \
                        ([]),                                                  \
                        ({ 130, 150, 100, 60, 60, 100 }),                      \
                        (["left hindleg":({85, 7}),                            \
                          "right hindleg":({85, 7}),                           \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          "tail":({65, 6})                                     \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"bites"}),                             \
                                "loc":({"maw"}),                               \
                            ]),                                                \
                          "slash":([                                           \
                                "hit":({"swipes"}),                            \
                                "loc":({"left paw", "right paw"}),             \
                            ]),                                                \
                          "bludgeon":([])                                      \
                          ]),                                                  \
                        ([ SS_SNEAK : 10, SS_HIDE : 10 ]),                     \
                        ([                                                     \
    SS_SNEAK          : ({ SS_SNEAK,          "sneaking",          50,  25 }), \
    SS_HIDE           : ({ SS_HIDE,           "hiding",            50,  25 }), \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "Leader of the Pride", "Leader of the Pride" }),    \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])

#define MUSTELIDAE  ([  "mustelidae"    : ({                                   \
                        "kit",                                                 \
                        "mustela",                                             \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :  ({"wolverine"}),                                \
        "AlpineTundra"      :  ({"badger", "wolverine"}),                      \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        (["ArcticTundra":({ ({"color"}), ({"pattern"}) })]),   \
                        ([]),                                                  \
                        ({ 140, 140, 100, 60, 60, 100 }),                      \
                        (["left hindleg":({85, 7}),                            \
                          "right hindleg":({85, 7}),                           \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          "tail":({65, 6})                                     \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"bites"}),                             \
                                "loc":({"maw"}),                               \
                            ]),                                                \
                          "slash":([                                           \
                                "hit":({"swipes"}),                            \
                                "loc":({"left paw", "right paw"}),             \
                            ]),                                                \
                          "bludgeon":([])                                      \
                        ]),                                                    \
                        ([ SS_AWARENESS : 10, SS_LOC_SENSE : 10 ]),            \
                        ([                                                     \
    SS_SNEAK          : ({ SS_SNEAK,          "sneaking",          50,  25 }), \
    SS_HIDE           : ({ SS_HIDE,           "hiding",            50,  25 }), \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "", "" }),                                          \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])

#define REPTILIA    ([  "reptilia"      : ({                                   \
                        "hatchling",                                           \
                        "reptile",                                             \
                        "carnivore",                                           \
                        ([                                                     \
        "ArcticTundra"      :   ({}),                                          \
        "AlpineTundra"      :   ({}),                                          \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        ([]),                                                  \
                        ([]),                                                  \
                        ({ 110, 140, 110, 60, 60, 120 }),                      \
                        (["left hindleg":({85, 7}),                            \
                          "right hindleg":({85, 7}),                           \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          "tail":({65, 6})                                     \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"bites"}),                             \
                                "loc":({"maw"}),                               \
                            ]),                                                \
                          "slash":([                                           \
                                "hit":({"swipes"}),                            \
                                "loc":({"left claws", "right claw"}),          \
                            ]),                                                \
                          "bludgeon":([])                                      \
                          ]),                                                  \
                        ([ SS_BLOCK : 15 ]),                                   \
                        ([                                                     \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "Aspect of the Dragon", "Aspect of the Dragon" }),  \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])
                    
#define SUIDAE      ([  "suidae"        : ({                                   \
                        "piglet",                                              \
                        "swine",                                               \
                        "omnivore",                                            \
                        ([                                                     \
        "ArcticTundra"      :   ({}),                                          \
        "AlpineTundra"      :   ({}),                                          \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        ([                                                     \
        "ArcticTundra"      :   ({}),                                          \
        "AlpineTundra"      :   ({}),                                          \
                                                                               \
        "AridDesert"        :   ({}),                                          \
        "SemiAridDesert"    :   ({}),                                          \
        "CoastalDesert"     :   ({}),                                          \
        "ColdDesert"        :   ({}),                                          \
                                                                               \
        "TemperateForest"   :   ({}),                                          \
        "TropicalForest"    :   ({}),                                          \
        "BorealForest"      :   ({}),                                          \
                                                                               \
        "TemperateGrassland":   ({}),                                          \
        "TropicalGrassland" :   ({}),                                          \
        "SteppeGrassland"   :   ({}),                                          \
                        ]),                                                    \
                        ([]),                                                  \
                        ({ 130, 100, 140, 60, 60, 110 }),                      \
                        (["left hindleg":({90, 10}),                           \
                          "right hindleg":({90, 10}),                          \
                          "left foreleg":({100, 10}),                          \
                          "right foreleg":({100, 10}),                         \
                          "body":({100, 40}),                                  \
                          "head":({100, 20}),                                  \
                          ]),                                                  \
                        (["impale":([                                          \
                                "hit":({"thrusts at"}),                        \
                                "loc":({"left tusk", "right tusk"}),           \
                            ]),                                                \
                          "slash":([]),                                        \
                          "bludgeon":([                                        \
                                "hit":({"charges"}),                           \
                                "loc":({"head first"}),                        \
                            ]),                                                \
                        ]),                                                    \
                        ([ SS_DEFENCE : 5, SS_HERBALISM : 5 ]),                \
                        ([                                                     \
    SS_TRACKING       : ({ SS_TRACKING,       "pick up a scent",   50,  25 }), \
    SS_AWARENESS      : ({ SS_AWARENESS,      "be aware",          50,  25 }), \
    SS_LOC_SENSE      : ({ SS_LOC_SENSE,      "know where you are",50,  25 }), \
    SS_HUNTING        : ({ SS_HUNTING,        "hunting",           50,  25 }), \
    SS_CLIMB          : ({ SS_CLIMB,          "climbing",          50,  25 }), \
    SS_SWIM           : ({ SS_SWIM,           "swimming",          50,  25 }), \
    SS_ACROBAT        : ({ SS_ACROBAT,        "acrobatics",        50,  25 }), \
    SS_MOUNTED_COMBAT : ({ SS_MOUNTED_COMBAT, "fighting mounted",  50,  25 }), \
    SS_DEFENCE        : ({ SS_DEFENCE,        "defending",         50,  25 }), \
    SS_BLIND_COMBAT   : ({ SS_BLIND_COMBAT,   "fighting blind",    50,  25 }), \
                        ]),                                                    \
                        ({ "", "" }),                                          \
                        ({}),                                                  \
                        ({}),                                                  \
                        }),                                                    \
                    ])

#define SCORPIO     ([  "scorpionoidea" : ({})                                 \
                    ])
                    
#define SPECIAL_CUB ([  "spider":"spiderling", "scorpion":"scorpling",         \
                        "frog":"froglet" ])

#define GUILD_RACES ([])
#define RACIAL_LIST ([])
#define RESTRICTION ([])

static mapping genus_list = ([]);

static mapping temp = ([
    "behaviour" : ([
        "fierce":"The @@query_race_name@@ looks menacing and wild, possessing a ferocious glare.",
        "energetic":"The @@query_race_name@@ has an abundant amount of energy, moving about vigorously.", 
        "guarded":"The @@query_race_name@@ appears cautious by nature, habitually keeping watch on its surroundings.", 
        "adventurous":"The @@query_race_name@@ displays curiosity towards is surroundings.", 
        "daring":"The @@query_race_name@@ daringly investigates its surroundings with curious intent.", 
        "docile":"The @@query_race_name@@ seems well trained and easy to handle.", 
        "meek":"The @@query_race_name@@ acts submissive, verging on docile.", 
        "timid":"The @@query_race_name@@ has a timorous personality, reacting to any noise.", 
        "aggressive":"The @@query_race_name@@ has an assertive presence, reacting aggressively without provocation.", 
        "savage":"The @@query_race_name@@ has a savage and untamed demeanor.", 
        "vicious":"The @@query_race_name@@ looks menacing and wild, seemingly inclined to ferocious acts.", 
        "tranquil":"The @@query_race_name@@ seems unaffected by commotion, unagitated.", 
        "gentle":"The @@query_race_name@@ has a gentle and warm manner.", 
        "gracious":"The @@query_race_name@@ has an aura of approachability, a graceful presence.", 
        "calm":"The @@query_race_name@@ moves in a calm pace, unaffected by its surroundings.", 
        "mannered":"The @@query_race_name@@ is composed and well-mannered."
    ]),
    "appearance": ([ 
        "disfigured":"Its @@query_fur@@ has been marred, it is now ragged and blemished.", 
        "marred":"It bears vicious scars of since long healed battle wounds, defacing its once pristine @@query_fur@@.", 
        "patchy":"Its @@query_fur@@ has fallen off in patches, leaving a less than pristine appearance.", 
        "underdeveloped":"It seems to be lacking in physical attributes, as if underdeveloped.", 
        "deformed":"It has developed poorly, leaving it misshapen and deformed.", 
        "mutilated":"It has been noticeably mutilated, its @@query_fur@@ marred with scars.", 
        "grotesque":"It has a grotesque appearance, beneath what little remains of its @@query_fur@@ you can clearly see patches of scabs and sores.", 
        "malformed":"There are protruding malformations clearly visible beneath its @@query_fur@@.", 
        "scarred":"It has been scarred from battle, the former wounds leaving marks in its @@query_fur@@", 
        "stained":"The @@query_fur@@ has clear and distinct markings.", 
        "pristine":"It looks to be in pristine condition, as if untouched by the world around it.", 
        "clean":"Its @@query_fur@@ is clean and well-kept, showing it has been tended with great care.", 
        "elegant":"Its @@query_fur@@ has a faint lustre, exuding elegance.", 
        "majestic":"It looks possitively majestic, a sublime specimen of the @@query_family@@ family.", 
        "well-bred":"It has been tended with great care, showing the dedication of its caretaker.", 
        "beautiful":"This @@query_family@@ is a beauty to behold.", 
        "cute":"It is a truly cute @@query_race_name@@, sure to gain plenty of adoration.",
    ]),
    "colours"   : ([ 
        "beige":"Its @@query_fur@@ possess a beige like luster.",
        "white":"Its @@query_fur@@ is completely white.",
        "pale":"The hue on its @@query_fur@@ is a palish grey.",
        "snow-white":"The colour of its @@query_fur@@ is that of the whitest snow.", 
        "black and white":"Its @@query_fur@@ shifts between black and white, forming well defined patterns.", 
        "pale-brown":"The @@query_fur@@ is of a pallid brown colour.", 
        "brown":"The @@query_fur@@ is brown in colour.", 
        "dark-brown":"The @@query_fur@@ is in a dark brown with a slight reddish hue.", 
        "black":"The @@query_fur@@ is black, lacking in hue and brightness.", ]),
    "locations" : ([ 
    "/d/Calia/gelan/rooms/blacksmith":({ "metal", "leather" }),
    "/d/Krynn/solamn/palanthas/merchants/smith":({ "metal" }),
    "/d/Krynn/solamn/palanthas/merchants/leather":({ "leather" }),
    "/d/Calia/gelan/rooms/grocery":({ "herbivore" }),
    "/d/Sparkle/guilds/new_merc/rooms/mess_hall":({ "carnivore" }),
    "/d/Sparkle/area/city/rooms/inside/inn":({ "omnivore" }),
    "/d/Sparkle/area/faerie/rooms/greenoaks/pub":({ "herbivore" })
    ]),
    "armours"   : ({ "armoured" }),
    //"sizes"     : ([ "hobbit":"small", "goblin":"small", "gnome":"small", "dwarf":"small", "elf":"normal", "human":"normal", "ogre":"huge", "small" :({ "small" }), "normal":({ "large", "big", "huge", "great", "massive", "enormous", "giant" }), "huge"  :({ "mammoth", "colossal", "titanic", "gigantic", "towering", "gargantuan",  "hulking" }) ]),
    "sizes"     : ([ "small" : 70, "modest" : 85, "medium" : 100, "large" : 115, "massive" : 130 ]),
    "vorare"    : ([ "omnivore":"It is an omnivore, able to consume any source of nutrients.", "herbivore":"It is a herbivore, only consuming plant life.", "carnivore":"A carnivorous creature, preying solely on animal flesh." ]),
]);

public int
save_temp(string dir)
{
    if (!mappingp(temp))
        return 0;
    
    save_map(temp, DATA + dir);
    return 1;
}

void
create()
{
    setuid();
    seteuid(getuid());
}

public int
add_genus(string genus, mapping genus_file)
{
    if (member_array(genus + ".o", get_dir(GENUS_LIST)) > -1)
        return 0;
    
    save_map(genus_file, GENUS_LIST + genus);

    return 1;
}

mixed
get_genus(mixed genus)
{
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!stringp(genus))
    {
        foreach(string genus_file: get_dir(GENUS_LIST))
        {
            genus_list[genus_file] = restore_map(GENUS_LIST + genus_file);
        }
        
        return genus_list;
    }
    
    if (!m_sizeof(genus_list[genus]))
    {
        if (member_array(genus + ".o", get_dir(GENUS_LIST)) < 0)
            return ([]);
    
        genus_list[genus] = restore_map(GENUS_LIST + genus);
    }
    
    return genus_list[genus];
}

public mapping
get_list(string name)
{
    mapping list;
    
    if (file_size(DATA + name + ".o") < 0)
        return ([]);
    
    if (mappingp(list = restore_map(DATA + name)))
        return list;
    
    return ([]);
}

public mixed
get_list_map(string name, string map)
{
    mapping list;
    
    if (!m_sizeof(list = get_list(name)))
        return -1;
    
    if (member_array(map, m_indexes(list)) < 0)
        return 0;
    
    return list[map];
}

public string
query_cub(mixed genus)
{
    if (IN_ARRAY(genus, m_indexes(SPECIAL_CUB)))
        return SPECIAL_CUB[genus];
    
    return get_genus(genus)["child"];
}

public string
query_fur(mixed genus)
{
    return get_genus(genus)["fur"];
}

public string
query_family(mixed genus)
{
    return get_genus(genus)["family"];
}

public string
query_name(mixed genus)
{
    return get_genus(genus)["common_name"];
}

public string
query_vorare(mixed genus)
{
    return get_genus(genus)["vorare"];
}

public varargs mixed
query_biome(mixed genus, string biome)
{
    if (!genus)
        return ({});
    
    if (biome)
        return get_genus(genus)["biome_list"][biome];
    
    return get_genus(genus)["biome_list"];
}

public mapping
query_vorare_desc()
{
    mapping vorare_desc;

    if (!mappingp(vorare_desc = get_list_map("genus", "vorare")))
        return ([]);
    
    return vorare_desc;
}

public mapping
query_appearance()
{
    mapping appearance;

    if (!mappingp(appearance = get_list_map("genus", "appearance")))
        return ([]);
    
    return appearance;
}

public mapping
query_behaviour()
{
    mapping behaviour;

    if (!mappingp(behaviour = get_list_map("genus", "behaviour")))
        return ([]);
    
    return behaviour;
}

public mapping
query_colours()
{
    mapping colours;

    if (!mappingp(colours = get_list_map("genus", "colours")))
        return ([]);
    
    return colours;
}

public varargs mixed
query_adjectives(mixed genus, string race)
{
    if (!genus)
        return ({ });
        
    if (race)
        return ({ get_genus(genus)["race_adj"][race],
                  m_indexes(query_behaviour()),
                  m_indexes(query_appearance()) });
    
    return get_genus(genus)["race_adj"];
}

public mapping
query_injuries(mixed genus)
{
    return get_genus(genus)["injuries"];
}

public int *
query_stats(mixed genus)
{
    return get_genus(genus)["stat_mod"];
}

public mapping
query_hitlocs(mixed genus)
{
    return get_genus(genus)["hitloc_mod"];
}

public mapping
query_special_attack(mixed genus)
{
    return get_genus(genus)["special_mod"];
}

public mapping
query_special_skills(mixed genus)
{
    return get_genus(genus)["special_skills"];
}

public mapping
query_pet_skills(mixed genus)
{
    return get_genus(genus)["skill_list"];
}

public mapping
query_genus_title(mixed genus)
{
    return get_genus(genus)["genus_title"];
}

public varargs string *
query_armour(string genus)
{
    string *armours;
    
    if (strlen(genus))
        return get_genus(genus)["armour_race"];
    
    if (!pointerp(armours = get_list_map("genus", "armours")))
        return ({});
    
    return armours;
}

public string
query_mm_out(mixed genus)
{
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!stringp(genus))
        return "";
    
    return get_genus(genus)["mm_out"];
}

public string
query_mm_in(mixed genus)
{
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!stringp(genus))
        return "";
    
    return get_genus(genus)["mm_in"];
}

public int
query_height(string genus, string race_name)
{
    mapping heights = get_genus(genus)["height"];
    if (!IN_ARRAY(race_name, m_indexes(heights)))
        return 0;
    
    return heights[race_name];
}

public string
query_pet_habitat(string genus)
{
    string habitat;
    if (!stringp(habitat = get_genus(genus)["habitat"]))
        return "ground";
    
    /* Know it doesnt make sense, but returns ground, air or water */
    return habitat;
}

public string *
query_guild_pets(string *guild, mixed genus)
{
    string *guilds = ({});
    
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!strlen(genus))
        return ({});
    
    if(!sizeof(guild))
        return ({});
    
    foreach(string gname: guild)
    {
        if (!IN_ARRAY(gname, m_indexes(get_genus(genus)["guild_pets"])))
            continue;
        
        guilds += get_genus(genus)["guild_pets"][gname];
    }
    
    return guilds;
}

public string *
query_racial_pets(string racial, mixed genus)
{
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!strlen(genus))
        return ({});
    
    if(!strlen(racial))
        return ({});
    
    if (!IN_ARRAY(racial, m_indexes(get_genus(genus)["racial_pets"])))
        return ({});
    
    return get_genus(genus)["racial_pets"][racial];
}

public string *
query_restrictions(string *restricted, mixed genus)
{
    string *restrictions = ({});
    
    if (objectp(genus))
        genus = genus->query_genus();
    
    if (!strlen(genus))
        return ({});
    
    if (!sizeof(restricted))
        return ({});
    
    foreach(string restrict: restricted)
    {
        if (!IN_ARRAY(restrict, m_indexes(get_genus(genus)["restrictions"])))
            continue;
        
        restrictions += get_genus(genus)["restrictions"][restricted];
    }
    
    return restrictions;
}

public string *
query_location(mixed room)
{
    string  filename,
           *location_list;
    mixed   location;
    
    if (objectp(room))
        filename = file_name(room);
    else if (stringp(room))
        filename = room;
    
    if (!stringp(filename))
        return ({});
    
    if (!mappingp(location = get_list_map("genus", "locations")))
        return ({});
    
    if (!pointerp(location_list = location[filename]))
        return ({});
    
    return location_list;
}

public varargs mixed *
query_genus_sizes(mixed size)
{
    mapping sizes;
    
    if (!mappingp(sizes = get_list_map("genus", "sizes")))
        return ({});

    if (stringp(size))
    {
        if (!IN_ARRAY(size, m_indexes(sizes)))
            return ({});

        return ({ sizes[size] });
    }

    return m_indexes(sizes);
}

public status
query_genus_rideable(object pet)
{
    string race, tamer, *rideable;
    
    if (!stringp(tamer = pet->query_tamer_name()))
        return 0;
    
    if (!stringp(race = MANAGER->query_pet_race(tamer)))
        return 0;
    
    if (!pointerp(rideable = get_genus(pet)["rideable"]))
        return 0;
    
    return IN_ARRAY(race, rideable);
}