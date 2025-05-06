import re
import math

def calculate_letters(text):
    """Zählt die Anzahl der Buchstaben im Text."""
    return sum(1 for char in text if char.isalpha())

def calculate_words(text):
    """Zählt die Anzahl der Wörter im Text."""
    # Wörter sind durch Leerzeichen getrennt
    return len(text.split())

def calculate_sentences(text):
    """Zählt die Anzahl der Sätze im Text."""
    # Sätze enden mit '.', '!' oder '?'
    return len(re.findall(r'[.!?]', text))

def main():
    # Eingabe des Textes vom Benutzer
    text = input("Enter a text: ")

    # Berechnung der Anzahl der Buchstaben, Wörter und Sätze
    letters = calculate_letters(text)
    words = calculate_words(text)
    sentences = calculate_sentences(text)

    # Vermeidung von Division durch Null, falls der Text keine Wörter enthält
    if words == 0:
        print("Before Grade 1")
        return

    # Berechnung von L (durchschnittliche Anzahl Buchstaben pro 100 Wörter)
    L = (letters / words) * 100

    # Berechnung von S (durchschnittliche Anzahl Sätze pro 100 Wörter)
    S = (sentences / words) * 100

    # Berechnung des Coleman-Liau-Index
    index = 0.0588 * L - 0.296 * S - 15.8

    # Rundung des Index auf die nächste Ganzzahl
    grade = round(index)

    # Ausgabe des Ergebnisses gemäß der Spezifikation
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()
