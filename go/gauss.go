package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

const MAXN = 2000 // Tamanho máximo da matriz

// Matrizes e vetores globais
var A [MAXN][MAXN]float64
var B [MAXN]float64
var X [MAXN]float64

func main() {
	// Lendo argumentos da linha de comando
	if len(os.Args) < 2 {
		fmt.Println("Uso: <dimensão da matriz>")
		return
	}

	n, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("Forneça um número válido para a dimensão da matriz")
		return
	}
	if n < 1 || n > MAXN {
		fmt.Printf("N = %d está fora do limite permitido.\n", n)
		return
	}

	// Inicializando matriz e vetor B
	inicializarMatriz(n)

	// Medindo o tempo de execução
	start := time.Now()
	eliminacaoGaussiana(n)
	duration := time.Since(start)

	// Exibir vetor solução X
	exibirResultado(n)

	fmt.Printf("Tempo de execução: %.3f ms\n", duration.Seconds()*1000)
}

// Função para inicializar a matriz A e vetor B com valores aleatórios
func inicializarMatriz(n int) {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			A[i][j] = rand.Float64() // Gera um número aleatório
		}
		B[i] = rand.Float64() // Preenchendo vetor B
		X[i] = 0.0
	}
}

// Implementação da eliminação de Gauss
func eliminacaoGaussiana(n int) {
	fmt.Printf("Executando eliminação de Gauss para uma matriz de dimensão %d...\n", n)

	// Etapa de eliminação
	for norm := 0; norm < n-1; norm++ {
		for row := norm + 1; row < n; row++ {
			multiplicador := A[row][norm] / A[norm][norm]
			for col := norm; col < n; col++ {
				A[row][col] -= A[norm][col] * multiplicador
			}
			B[row] -= B[norm] * multiplicador
		}
	}

	// Substituição regressiva para encontrar X
	for row := n - 1; row >= 0; row-- {
		X[row] = B[row]
		for col := row + 1; col < n; col++ {
			X[row] -= A[row][col] * X[col]
		}
		X[row] /= A[row][row]
	}
}

// Exibir vetor solução X (caso seja pequeno o suficiente)
func exibirResultado(n int) {
	if n < 100 {
		fmt.Print("\nX = [")
		for i := 0; i < n; i++ {
			fmt.Printf("%.2f", X[i])
			if i < n-1 {
				fmt.Print("; ")
			} else {
				fmt.Println("]")
			}
		}
	}
}
