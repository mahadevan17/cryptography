#simple public key crytography RSA
#***** p,q should be known only to sender and receiver
#n=p*q, d=e^-1mod Euler_totenit(n)
#ct=pt**e mod p*q
#pt=ct**d mod p*q
#public key n,e
#private key n,d

import random as ran

def gcd(a,b):
    if a<b:
        a,b=b,a
    while b != 0:
        c = a % b
        a = b
        b = c
    return a

    
def Euler_tot(p,q):
    if (p==q):
        return (p**2)-p   #if p*q is of form prime^k return (p^k)-p^(k-1)
    
    return (p-1)*(q-1)    #if p,q are prime numbers then return (p-1)*(q-1)


def rsa_encryption(pt,p,q,t,e):
    #p,q,
    
    encrypted=(pt**e) % (p*q)

    return encrypted

def rsa_decryption(ct,p,q,t,e):
    try:
        d=pow(e,-1,t)
    except(ValueError):
        return "chosen e does not have a invertible try again"
        
    decrypted=(ct**d) % (p*q)

    return decrypted


#main

pt=int(input("enter the plaintext: "))

p=int(input("enter p: "))
q=int(input("enter q: "))

t=Euler_tot(p,q)
e=ran.randint(2,t)
while(gcd(e,t)!=1):
    e=ran.randint(2,t)
ct=rsa_encryption(pt,p,q,t,e)
print("ct: ",ct)
print("pt: ",rsa_decryption(ct,p,q,t,e))
    
    

    
    
