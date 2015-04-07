Designing degenerate primers
============================

1. We try to design a degenerate primer for a protein called sericine,
    usually found in silk-producing organisms.

2. From the NCBI website we retrieve a couple of protein sequences
    for the protein of interest and download them in `sequence.fasta` file.

    We ensure that the protein sequences are within 600-900 aa in length.

3. A clustalW alignment is performed and obtained multiple sequence alignment
    is saved in file `clustalw-alignment.clustalw`.


Now we examine the start and end sequences of obtained alignment file.

The alignment start for similar nature of organisms is: MRFVLCC
The alignment end for similar nature of organisms is  : LRKNIGV

As we can see, both of these short sequences contain L, R; the amino acids
that we tend to avoid in primer design (because of degeneracy). For this, we
consult different online databases that enlist the codon usage pattern in
the organism of our interest and try to locate the pattern.

This information can help us design more specific primers (although primer
is intended to be degenerate, we don't want the degeneracy to be too high to
reduce the specificity).

4. Corresponding to both these peptide sequences, we design an oligonucleotide,
    accounting suitably for degenracy.

For example,

For forward primer, MRFVLCC

M - ATG
R - (A + C)G(A + T + G + C)  = MGN
F - TT(C + T)                = TTY
V - GT(A + T + G + C)        = GTN
L - (C + T)T(A + T + G + C)  = YTN
C - TG(C + T)                = TGY

Complete sequence: ATGMGNTTYGTNYTNTGY

For reverse primer, LRKNIGV

R - (A + C)G(A + T + G + C)  = MGN
K - AA(A + G)                = AAR
N - AA(C + T)                = AAY
I - AT(A + T + C)            = ATH
G - GG(A + T + G + C)        = GGN
V - GT(A + T + G + C)        = GTN

Complete sequence: MGNAARAAYATHGGNGTN

Reverse complement: NACNCCGATRTTYTTNCK (Final)

Here we can note that R unnecessarily introduces a degeneracy in form of N. Hence,
we can drop that amino acid without any harm.

NOTE:
-----
1. While designing primers, ensure that you avoid L, R, S amino acids as much as
    possible. Simply because they are highly degenerate and are coded by 6 codons.

2. We try to avoid degeneracy at the 3' end of the sequence because that is where
    polymerase starts the synthesis. Non degenracy would ensure correctness and
    accurate PCR product.
