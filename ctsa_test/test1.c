#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "wavefront/wavefront_align.h"

int main() {
    char *pattern = "A";
    char *text    = "ABC";

    wavefront_aligner_attr_t attr = wavefront_aligner_attr_default;
    attr.distance_metric = gap_linear;
    attr.linear_penalties.match = -1;
    attr.linear_penalties.mismatch = 1;
    attr.linear_penalties.indel = 1;
    attr.alignment_scope = compute_alignment;

    attr.alignment_form.span = alignment_endsfree;
    attr.alignment_form.pattern_begin_free = 0;
    attr.alignment_form.pattern_end_free = 0;
    attr.alignment_form.text_begin_free = 0;
    attr.alignment_form.text_end_free = 2;

    wavefront_aligner_t* const wf_aligner = wavefront_aligner_new(&attr);
    wavefront_align(wf_aligner, pattern, strlen(pattern), text, strlen(text));
    cigar_print_pretty(stderr,
      pattern,strlen(pattern),text,strlen(text),
      wf_aligner->cigar,wf_aligner->mm_allocator);

    fprintf(stderr,"Alignment Score %d\n",wf_aligner->cigar->score);

    wavefront_aligner_delete(wf_aligner);
}
