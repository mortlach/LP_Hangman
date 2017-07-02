class gematria():
    def __init__(self):
        self.latin_fragments = ['F', 'U', 'TH', 'O', 'R', 'C', 'G', 'W', 'H', 'N', 'I',
                                'J', 'EO', 'P', 'X', 'S', 'T', 'B', 'E', 'M', 'L', 'NG',
                                'OE', 'D', 'A', 'AE', 'Y', 'IA', 'EA']
        self.period      = "."
        self.quote       = "\""
        self.apostrophe  = "'"
        self.colon       = ":"
        self.semicolon   = ";"
        self.comma       = ","
        self.exclamation = "!"
        self.question    = "?"
        self.bigram = ['TH', 'EO', 'NG', 'OE', 'AE', 'IA', 'IO', 'EA']
        self.trgram = 'ING'

    def translate_to_gematria(self, word):  # thanks to 'solvers
        res = []
        skip = 0
        WORD = word.upper()
        for i, val in enumerate(WORD):
            if skip:
                skip -= 1
                continue
            if WORD[i:i + 3] == self.trgram:
                res.append(self.trgram)
                skip += 2
                continue
            if WORD[i:i + 2] in self.bigram:
                res.append(WORD[i:i + 2])
                skip += 1
                continue
            res.append(val)
        return res