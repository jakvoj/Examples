Sub MazaniPracSesit()
    Range("D3:AD270").Select()
    Selection.ClearContents()
    Range("AE1").Select()
End Sub

Sub VytvoreniSeznamu()
    Range("D3:AD270").Select()
    Selection.ClearContents()
    Range("B7:AD270").Select()
    Selection.Delete(Shift:=xlUp)
    Dim b As Integer
    b = 3
    Dim a As Integer
    a = 6
    Dim bb As Integer
    bb = 7
    Dim datum As Integer
    datum = 1
    Dim oznaceni As String
    Dim datumpole As String
    Dim Kontrola As String
    Dim kontrolapom As String
    Do Until Kontrola = "1."
        oznaceni = "B" & b & ":AD" & a
        datumpole = "B" & bb
        Range(oznaceni).Select()
        Selection.Copy()
        ActiveCell.Offset(1, 0).Select()
        ActiveSheet.Paste()
        Range(datumpole).Select()
        ActiveCell.Value = "= $B$1 + " & datum
        kontrolapom = ActiveCell.Value
        ActiveCell.Offset(0, 1).Value = "= $B$1 + " & datum
        Kontrola = Mid(kontrolapom, 1, 2)
        b = b + 4
        a = a + 6
        bb = bb + 4
        datum = datum + 1
    Loop
    Range(ActiveCell.Offset(0, 0), ActiveCell.Offset(0, 28)).Select()
    Selection.Delete()
    Range("AE1").Select()
End Sub

Sub PridaniRadku()
    Range("B3").Select()
    Dim Kontrola As String
    Dim datumcitac As Integer
    datumcitac = -1
    Kontrola = "_"
    Do Until Kontrola = ""
        Kontrola = ActiveCell.Value
        ActiveCell.Offset(1, 0).Select()
        datumcitac = datumcitac + 1
    Loop
    ActiveCell.Offset(-2, 0).Select()
    Range(ActiveCell.Offset(0, 0), ActiveCell.Offset(0, 28)).Select()
    Selection.Copy()
    ActiveCell.Offset(1, 0).Select()
    ActiveSheet.Paste()
    ActiveCell.Value = "= $B$1 + " & datumcitac
    ActiveCell.Offset(0, 1).Select()
    ActiveCell.Value = "= $B$1 + " & datumcitac
End Sub

Sub OdstraneniRadku()
    Range("B3").Select()
    Dim Kontrola As String
    datumcitac = -1
    Kontrola = "_"
    Do Until Kontrola = ""
        Kontrola = ActiveCell.Value
        ActiveCell.Offset(1, 0).Select()
    Loop
    ActiveCell.Offset(-2, 0).Select()
    Range(ActiveCell.Offset(0, 0), ActiveCell.Offset(0, 28)).Select()
    Selection.Delete()
End Sub

Sub ZaznamenaniDoProcent() 'zaznamenávání je omezeno na daný mìsíc, den v B1 musí být jednociferný
    Sheets("Nastavení - Informace").Select() 'nastaveni
    Dim HracKod(30) As String
    Dim HracPrijmeni(30) As String
    Range("D6").Select()
    Dim Index As Integer
    Index = 0
    Do Until ActiveCell.Value = ""
        HracKod(Index) = ActiveCell.Value
        ActiveCell.Offset(0, 1).Select()
        HracPrijmeni(Index) = ActiveCell.Value
        ActiveCell.Offset(1, -1).Select()
        Index = Index + 1
    Loop
    Index = Index - 1
    'nastaveni
    Sheets("PRAC").Select()
    'konec
    Range("B3").Select()
    Dim konecRetezec As String
    Dim celkemRadek As Integer
    celkemRadek = 0
    Do Until konecRetezec = "1." Or ActiveCell.Value = ""
        ActiveCell.Offset(1, 0).Select()
        konecRetezec = Mid(ActiveCell.Value, 1, 2)
        celkemRadek = celkemRadek + 1
    Loop
    celkemRadek = 4 * celkemRadek
    'konec
    Range("E3").Select()
    Dim KonecRadky As Integer
    KonecRadky = 0
    Dim HracProcenta(30) As Integer
    Dim celkemPolicek As Integer
    celkemPolicek = celkemRadek * 24
    Do Until celkemPolicek = 0
        'skenování
        Dim i As Integer
        For i = 0 To Index
            If HracKod(i) = ActiveCell.Value Then
                HracProcenta(i) = HracProcenta(i) + 1
            End If
        Next i
        'skenování
        If KonecRadky < 23 Then
            ActiveCell.Offset(0, 1).Select()
        End If
        If KonecRadky = 23 Then
            ActiveCell.Offset(1, -23).Select()
            KonecRadky = -1
        End If
        KonecRadky = KonecRadky + 1
        celkemPolicek = celkemPolicek - 1
    Loop
    'mìsíc
    Dim mesic As String
    Dim mesicPom As String
    Dim scanPolicko As String
    mesicPom = Range("B1").Value
    If Mid(mesicPom, 4, 1) = "." Then
        mesic = Mid(mesicPom, 3, 1)
    Else
        mesic = Mid(mesicPom, 3, 2)
    End If
    'mìsíc
    Sheets("Procenta").Select()
    Range("E8").Select()
    Dim a As Integer
    For a = 0 To 10
        If ActiveCell.Offset(-1, 0).Value = mesic Then
            Exit For
        End If
        ActiveCell.Offset(0, 1).Select()
    Next a
    Dim posuv As Integer
    posuv = 0
    Do Until Range("C8").Offset(posuv, 0).Value = ""
        Dim b As Integer
        For b = 0 To Index
            If HracPrijmeni(b) = Range("C8").Offset(posuv, 0).Value Then
                ActiveCell.Value = HracProcenta(b)
            End If
        Next b
        ActiveCell.Offset(1, 0).Select()
        posuv = posuv + 1
    Loop
    Sheets("PRAC").Select()
    Range("AE1").Select()
End Sub

Sub VytvoritAVyplnitNovyVykaz()
    'nastaveni
    Sheets("Nastavení - Informace").Select()
    Dim HracKod(30) As String
    Dim HracPrijmeni(30) As String
    Range("D6").Select()
    Dim Index As Integer
    Index = 0
    Do Until ActiveCell.Value = ""
        HracKod(Index) = ActiveCell.Value
        ActiveCell.Offset(0, 1).Select()
        HracPrijmeni(Index) = ActiveCell.Value
        ActiveCell.Offset(1, -1).Select()
        Index = Index + 1
    Loop
    Index = Index - 1
    'nastaveni
    Sheets("Nový výkaz").Select()
    'Vytvoreni
    Range("E4:E42").Select()
    Selection.Borders(xlEdgeTop).Weight = xlThin
    Selection.Borders(xlEdgeBottom).Weight = xlThin
    Selection.Borders(xlEdgeRight).Weight = xlThin
    Selection.Borders(xlEdgeLeft).Weight = xlThin
    Range("E4:AZ4").Select()
    Selection.Delete(Shift:=xlToLeft)
    Range("F5:AZ42").Select()
    Selection.Delete(Shift:=xlToLeft)
    Range("E5:E42").Select()
    Dim DatumPricet As Integer
    Dim DatumKontrola As String
    DatumKontrola = ""
    DatumPricet = 1
    Do Until DatumKontrola = "1."
        Selection.Copy()
        ActiveCell.Offset(0, 1).Select()
        ActiveSheet.Paste()
        ActiveCell.Value = "= $C$4 + " & DatumPricet
        ActiveCell.Offset(1, 0).Value = "= $C$4 + " & DatumPricet
        DatumPricet = DatumPricet + 1
        DatumKontrola = Mid(ActiveCell.Value, 1, 2)
    Loop
    Selection.Delete(Shift:=xlToLeft)
    ActiveCell.Offset(-1, -1).Select()
    Range(ActiveCell, "E4").Select()
    Selection.Merge()
    Selection.HorizontalAlignment = xlCenter
    Selection.VerticalAlignment = xlCenter
    Selection.Font.Name = "Arial"
    Selection.Font.Size = 11
    Selection.Font.Bold = True
    Selection.Interior.Color = 16777164
    ActiveCell.Value = "Den"
    Range("E4:E42").Select()
    Selection.Borders(xlEdgeTop).Weight = xlMedium
    Selection.Borders(xlEdgeBottom).Weight = xlMedium
    Selection.Borders(xlEdgeRight).Weight = xlMedium
    Selection.Borders(xlEdgeLeft).Weight = xlMedium
    Range("Z1").Select()
    'Vytvoreni
    'Vyplneni
    'faze 1
    Dim poprvy As Boolean
    poprvy = True
    Dim Hrani As String
    Hrani = "z"
    Sheets("PRAC").Select()
    Dim HracVykaz(30) As String
    Range("E3").Select()
    Do Until False
        Dim i As Integer
        Dim j As Integer
        For i = 0 To 23
            For j = 0 To Index
                If HracKod(j) = ActiveCell.Value Then
                    HracVykaz(j) = HracVykaz(j) + Hrani
                End If
            Next j
            If i = 11 Then
                ActiveCell.Offset(1, -11).Select()
            Else
                If i < 23 Then
                    ActiveCell.Offset(0, 1).Select()
                End If
            End If
        Next i
        Sheets("Nový výkaz").Select()
        If poprvy = True Then
            Range("E7").Select()
            poprvy = False
        End If
        Dim posuv As Integer
        posuv = 0
        Do Until Range("C7").Offset(posuv, 0).Value = ""
            Dim VykazPrijmeni As String
            Dim k As Integer
            For k = 1 To 100
                If Mid(Range("C7").Offset(posuv, 0).Value, k, 1) = " " Then
                    Exit For
                End If
                VykazPrijmeni = VykazPrijmeni + Mid(Range("C7").Offset(posuv, 0).Value, k, 1)
            Next k
            Dim l As Integer
            For l = 0 To Index
                If VykazPrijmeni = UCase(HracPrijmeni(l)) Then
                    ActiveCell.Value = ActiveCell.Value + HracVykaz(l)
                End If
            Next l
            ActiveCell.Offset(3, 0).Select()
            VykazPrijmeni = ""
            If posuv = 0 Then
                posuv = posuv + 1
            Else
                posuv = posuv + 3
            End If
        Loop
        ActiveCell.Offset(-36, 1).Select()
        If ActiveCell.Offset(-1, 0).Value = "" Then
            Exit Do
        End If
        Dim a As Integer
        For a = 0 To Index
            HracVykaz(a) = ""
        Next a
        Sheets("PRAC").Select()
        ActiveCell.Offset(3, -11).Select()
    Loop
    'faze 1
    'faze 2
    For a = 0 To Index
        HracVykaz(a) = ""
    Next a
    poprvy = True
    Hrani = "z"
    Sheets("PRAC").Select()
    Range("E5").Select()
    Do Until False
        For i = 0 To 23
            For j = 0 To Index
                If HracKod(j) = ActiveCell.Value Then
                    HracVykaz(j) = HracVykaz(j) + Hrani
                End If
            Next j
            If i = 11 Then
                ActiveCell.Offset(1, -11).Select()
            Else
                If i < 23 Then
                    ActiveCell.Offset(0, 1).Select()
                End If
            End If
        Next i
        Sheets("Nový výkaz").Select()
        If poprvy = True Then
            Range("E8").Select()
            poprvy = False
        End If
        posuv = 0
        Do Until Range("C7").Offset(posuv, 0).Value = ""
            For k = 1 To 100
                If Mid(Range("C7").Offset(posuv, 0).Value, k, 1) = " " Then
                    Exit For
                End If
                VykazPrijmeni = VykazPrijmeni + Mid(Range("C7").Offset(posuv, 0).Value, k, 1)
            Next k
            For l = 0 To Index
                If VykazPrijmeni = UCase(HracPrijmeni(l)) Then
                    ActiveCell.Value = ActiveCell.Value + HracVykaz(l)
                End If
            Next l
            ActiveCell.Offset(3, 0).Select()
            VykazPrijmeni = ""
            If posuv = 0 Then
                posuv = posuv + 1
            Else
                posuv = posuv + 3
            End If
        Loop
        ActiveCell.Offset(-36, 1).Select()
        If ActiveCell.Offset(-2, 0).Value = "" Then
            Exit Do
        End If
        For a = 0 To Index
            HracVykaz(a) = ""
        Next a
        Sheets("PRAC").Select()
        ActiveCell.Offset(3, -11).Select()
    Loop
    'faze 2
    'faze 3
    For a = 0 To Index
        HracVykaz(a) = ""
    Next a
    poprvy = True
    Hrani = "PR"
    Sheets("PRAC").Select()
    Range("Q3").Select()
    Do Until False
        For i = 0 To 23
            For j = 0 To Index
                If HracKod(j) = ActiveCell.Value Then
                    HracVykaz(j) = HracVykaz(j) + Hrani
                End If
            Next j
            If i = 11 Then
                ActiveCell.Offset(1, -11).Select()
            Else
                If i < 23 Then
                    ActiveCell.Offset(0, 1).Select()
                End If
            End If
        Next i
        Sheets("Nový výkaz").Select()
        If poprvy = True Then
            Range("E8").Select()
            poprvy = False
        End If
        posuv = 0
        Do Until Range("C7").Offset(posuv, 0).Value = ""
            For k = 1 To 100
                If Mid(Range("C7").Offset(posuv, 0).Value, k, 1) = " " Then
                    Exit For
                End If
                VykazPrijmeni = VykazPrijmeni + Mid(Range("C7").Offset(posuv, 0).Value, k, 1)
            Next k
            For l = 0 To Index
                If VykazPrijmeni = UCase(HracPrijmeni(l)) Then
                    ActiveCell.Value = ActiveCell.Value + HracVykaz(l)
                End If
            Next l
            ActiveCell.Offset(3, 0).Select()
            VykazPrijmeni = ""
            If posuv = 0 Then
                posuv = posuv + 1
            Else
                posuv = posuv + 3
            End If
        Loop
        ActiveCell.Offset(-36, 1).Select()
        If ActiveCell.Offset(-2, 0).Value = "" Then
            Exit Do
        End If
        For a = 0 To Index
            HracVykaz(a) = ""
        Next a
        Sheets("PRAC").Select()
        ActiveCell.Offset(3, -11).Select()
    Loop
    'faze 3
    'faze 4
    For a = 0 To Index
        HracVykaz(a) = ""
    Next a
    poprvy = True
    Hrani = "PR"
    Sheets("PRAC").Select()
    Range("Q5").Select()
    Do Until False
        For i = 0 To 23
            For j = 0 To Index
                If HracKod(j) = ActiveCell.Value Then
                    HracVykaz(j) = HracVykaz(j) + Hrani
                End If
            Next j
            If i = 11 Then
                ActiveCell.Offset(1, -11).Select()
            Else
                If i < 23 Then
                    ActiveCell.Offset(0, 1).Select()
                End If
            End If
        Next i
        Sheets("Nový výkaz").Select()
        If poprvy = True Then
            Range("E9").Select()
            poprvy = False
        End If
        posuv = 0
        Do Until Range("C7").Offset(posuv, 0).Value = ""
            For k = 1 To 100
                If Mid(Range("C7").Offset(posuv, 0).Value, k, 1) = " " Then
                    Exit For
                End If
                VykazPrijmeni = VykazPrijmeni + Mid(Range("C7").Offset(posuv, 0).Value, k, 1)
            Next k
            For l = 0 To Index
                If VykazPrijmeni = UCase(HracPrijmeni(l)) Then
                    ActiveCell.Value = ActiveCell.Value + HracVykaz(l)
                End If
            Next l
            ActiveCell.Offset(3, 0).Select()
            VykazPrijmeni = ""
            If posuv = 0 Then
                posuv = posuv + 1
            Else
                posuv = posuv + 3
            End If
        Loop
        ActiveCell.Offset(-36, 1).Select()
        If ActiveCell.Offset(-3, 0).Value = "" Then
            Exit Do
        End If
        For a = 0 To Index
            HracVykaz(a) = ""
        Next a
        Sheets("PRAC").Select()
        ActiveCell.Offset(3, -11).Select()
    Loop
    'faze 4
    Range("D1").Select()
    'Vyplneni
End Sub

Sub SmazatNovyVykaz()
    Range("E7:AZ42").Select()
    Selection.ClearContents()
    Range("Z1").Select()
End Sub

Sub ZamknoutNastaveni()
    ActiveSheet.Protect(DrawingObjects:=True, Contents:=True, Scenarios:=True)
End Sub

Sub OdemknoutNastaveni()
    ActiveSheet.Unprotect()
End Sub