# Serra Automatica con Arduino 🌱

Questo progetto illustra come realizzare una serra automatizzata utilizzando Arduino per gestire vari parametri ambientali essenziali per la crescita delle piante.

## Descrizione

La serra automatizzata è progettata per monitorare e gestire:
- **Temperatura e umidità dell'aria**
- **Livello di umidità del terreno**
- **Illuminazione automatica** in base alla luce esterna
- **Ventilazione** per mantenere condizioni ottimali
- **Irrigazione automatica** in base ai dati del terreno
- **Livello dell'acqua nel serbatoio**, con allarme visivo e sonoro in caso di riserva insufficiente.

## Componenti Utilizzati

### Elettronici
- Arduino Uno
- Sensore di umidità del terreno (igrometro)
- Sensore di temperatura e umidità DHT11
- Fotoresistore per rilevare il livello di luce
- Sensore di livello dell'acqua
- Pompa ad immersione
- Ventola
- Buzzer e LED
- Display LCD con interfaccia I2C
- Modulo relè (per alimentare pompa, ventola e luci a 220V)

### Strutturali
- Box in plexiglass (100x60x40 cm)
- Serbatoio per l'acqua
- Pannello di compensato per simulare il terreno

## Funzionalità

1. **Visualizzazione dei dati su display**: monitoraggio in tempo reale di temperatura, umidità, luce, umidità del terreno e livello dell'acqua.
2. **Irrigazione automatica**: attivazione della pompa in base all'umidità del terreno.
3. **Gestione della luce**: accensione delle luci LED quando la luminosità esterna è insufficiente.
4. **Gestione della ventilazione**: attivazione della ventola per ridurre l'umidità in eccesso.
5. **Allarme livello acqua**: segnalazione visiva e sonora in caso di serbatoio vuoto.

## Come Utilizzare

1. **Assemblare i componenti**: Segui lo schema incluso nei file del progetto.
2. **Caricare il codice su Arduino**:
   - Utilizza l'IDE Arduino per caricare il file `gestione_serra.ino` sulla scheda.
3. **Configurare la serra**: Collega i sensori e i moduli come descritto nella guida.
4. **Testare le funzionalità**: Verifica che i dati siano correttamente visualizzati sul display e che le azioni automatiche funzionino come previsto.

## Struttura del Codice

- **setup()**: Configura i pin e i dispositivi collegati.
- **loop()**: Esegue ciclicamente:
  - Rilevazione e visualizzazione dei dati.
  - Controllo dei sensori per attivare le azioni necessarie (es. pompa, ventilazione, luci).
- **Funzioni dedicate**:
  - `gestioneLuce()`: Regola l'illuminazione.
  - `gestioneVentilazione()`: Controlla la ventola.
  - `gestioneIrrigazione()`: Attiva la pompa in base all'umidità del terreno.
  - `gestioneSerbatoio()`: Controlla il livello dell'acqua e gestisce l'allarme.

## Requisiti Software 💻

- Arduino IDE (versione >= 1.8.0)
- Librerie:
  - `LiquidCrystal_I2C.h`
  - `SimpleDHT.h`
