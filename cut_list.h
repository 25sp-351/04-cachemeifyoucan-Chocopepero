#ifndef CUT_LIST_H
#define CUT_LIST_H

#include "piece_values.h"
#include "vec.h"

typedef struct {
    Vec groups;
    PieceLength remainder;
    int total_value;
} CutList;

typedef struct pg {
    PieceLengthValue pv;
    int count;
} PieceGroup;

typedef struct {
    Vec value_list;
    unsigned int rod_len;
    CutList *input_cutlist;
} InputValues;

CutList *new_cutlist(Vec length_and_values, PieceLength length);
CutList *cutlist_copy(CutList *cl);
void cutlist_free(CutList *cl);
bool cutlist_can_add_piece(CutList *cl, PieceLengthValue pv);
CutList *cutlist_add_piece(CutList *cl, PieceLengthValue pv);
void cutlist_print(CutList *cl);
CutList *_optimize(CutList *starting_cutlist, Vec pv);
unsigned int prompt_for_length();

#endif
