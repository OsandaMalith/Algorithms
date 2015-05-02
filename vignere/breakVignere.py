from collections import Counter
import string
'''
http://osandamalith.wordpress.com
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
'''

cipher = "FB50F7C621B40EC24CB2C63BA80EC75EFCD526AC49CE1FFDD473B946CE1FFBDF32AA47C55EE6DB3CA30ECA51F69227A54B8B4FF3C120A441C54CBC921AB90ED95AFED327A85D8B4BFD9224A54FDF5AE4D721ED49C249F7C173A443C65AF6DB32B94B8B4FFED732BE5BD95AB2DD21ED5ECA56FC9227A20EDF57F7923BB843CA51B2DF3AA34A851FDBC673AE41C65AE1923BA243CE1FE6DD73B946CE1FF0DD20A243D81FF3DC37ED4CDE4CFBDC36BE5DCE4CB2DD35ED43CE51A99235A25C8B51FDC63BA440CC1FF0C727ED59C35EE69230A243CE4CB2DA3CA04B8B4BFD9227A54BC61FFBDC73B946CE1FFFDD20B90ECC5AFCD721AC428B5EFCD673A440DF5AFEDE3AAA47C953F79220A54FDB5AB2D132A30EC95AB2D373BE5BC955F7D127ED48C44DB2C23CA85AD946BC9203A24BDF4DEB923ABE0EDF57F79226A347DD5AE0C132A10EC75EFCD526AC49CE1FE5DA3AAE468B4BFAD773A54BCA4DE6923BA242CF4CB2C53AB9468B51F3C626BF4B8B5EFCD673A45AD85AFED47DED66CE1FE5DA3CED46CA4CB2D373AE41C54BF7DF23B90ECD50E09223A24BDF4DEB9230AC40C550E6923BAC58CE1FFFC730A50ED95AE1C236AE5A8B59FDC073A547C64CF7DE35E10EC44DB2D43CBF0ECA51EBC63BA440CC1FF7DE20A8008B68FAD721A858CE4DB2C63BA85CCE1FFBC173AC0ED85AFCC136ED41CD1FF0D732B85AD213B2DD21ED5EC448F7C07FED41D91FFAD321A041C546BE9232BE0EC251B2C63BA80EC650E6DB3CA30EC459B2D373BA4FDD5AB2DD35ED5AC35AB2C136AC028B56FC9227A54B8B58E0DD24B9468B50F49232ED48C750E5D721E10EDF57F7C036ED47D81FE2DD36B95CD21FFBDC73A45AD81FF0DB21B94685"

ENGLISH_FREQ = {'A':0.08167, 'B':0.01492, 'C':0.02782, 'D':0.04253, 'E':0.12702,
                'F':0.02228, 'G':0.02015, 'H':0.06094, 'I':0.06966, 'J':0.00153,
                'K':0.00772, 'L':0.04025, 'M':0.02406, 'N':0.06749, 'O':0.07507,
                'P':0.01929, 'Q':0.00095, 'R':0.05987, 'S':0.06327, 'T':0.09056,
                'U':0.02758, 'V':0.00978, 'W':0.02360, 'X':0.00150, 'Y':0.01974,
                'Z':0.00074}

number =[i for i in range(48,58)]
upper_case = string.ascii_uppercase
lower_case = string.ascii_lowercase
lst_cipher = [cipher[i:i+2] for i in range(0,len(cipher),2)]
key_length=7

def hexxor(a, b):
    return "".join(["%x" % (int(x, 16) ^ int(y, 16)) for (x, y) in zip(a, b)])

# break cipher into shift into each block of key length
def shift_chunk():
    shift=[]
    for i in range(key_length):
        shift.append(lst_cipher[i::key_length])
    return shift

shift = shift_chunk()

# calculate frequency of each hex character in cipher
def letter_count(message):
    mes_lst = [message[i:i+2] for i in range(0,len(message),2)]
    return dict((k, v) for k,v in Counter(mes_lst).most_common())

# calculate frequency of each letter in any message
def letter_count_2(message):
    return dict((k, v) for k,v in Counter(message).most_common())

# calculate index of coincidence of cipher
# as result, we achieve max IC and assume key length is corresponding
def calculateIC(message):
        cipher = message
        dict_IC = {}
        for key in range(1,14):
            average_IC = 0
            for i in range(key):
                t_cipher = ''.join([cipher[i:i+2] for i in range(0,len(message),2*key)])
                num_letter = letter_count(t_cipher)
                IC = 0
                fixed = len(t_cipher)/2*(len(t_cipher)/2-1)
                for i in num_letter:
                    f = num_letter[i]*(num_letter[i]-1)
                    if fixed == 0:
                        IC+=0
                    else:
                        IC += float(f)/fixed
                average_IC += IC
            dict_IC[key] = average_IC/(key)
        return dict_IC

# calculate all of candidate byte that XOR with each shift we get result that
# in range (32,126) and not a number
def guess_byte(n):
    right_guess=[]
    for i in range(255):
        hex_i = '{:02X}'.format(i)
        k=0
        for j in shift[n]:
            c = int(hexxor(hex_i,j),16)
            if c<32 or c>126 or c in number:
                break
            k+=1
        if k==len(shift[n]):
            right_guess.append(hex_i)
    return right_guess

# calculate chi square of message
def chi_square(mess):
    t_mess=""
    for i in mess:
        if i in lower_case or i in upper_case:
            t_mess+=i
    chi = 0
    t_mess = t_mess.upper()
    dic_mess =  letter_count_2(t_mess)
    for i in upper_case:
        b = ENGLISH_FREQ[i]*len(t_mess)
        if i in dic_mess:
            a = (dic_mess[i] - b)**2
            chi += a/b
        else:
            chi+=b
    return chi

# calculate all ci square of all messages those are correspond with guess byte
# obtain the min chi
def chiCal(index):
    guess_list = guess_byte(index)
    chi = {}
    for i in guess_list:
        guess_mess=[]
        for j in shift[index]:
            guess_mess.append(hexxor(i,j).decode('hex'))
        chi[i] = chi_square(''.join(guess_mess))
    min_chi = min(chi, key=chi.get)
    return min_chi


# calculate key
key=""
for i in range(key_length):
    key+= chiCal(i)

# calculate plaintext
plaintext=""
for i in range(0,len(cipher),key_length*2):
    plaintext+=hexxor(cipher[i:i+key_length*2],key).decode('hex')
print plaintext
