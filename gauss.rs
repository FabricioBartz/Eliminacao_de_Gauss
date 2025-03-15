use std::env;
use rand::Rng;
use std::time::Instant;

const MAXN: usize = 2000; // Tamanho máximo da matriz

// Matrizes e vetores globais
static mut A: [[f64; MAXN]; MAXN] = [[0.0; MAXN]; MAXN];
static mut B: [f64; MAXN] = [0.0; MAXN];
static mut X: [f64; MAXN] = [0.0; MAXN];

fn main() {
    // Lendo argumentos da linha de comando
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Uso: {} <dimensão da matriz>", args[0]);
        return;
    }
    
    let n: usize = args[1].parse().expect("Forneça um número válido para a dimensão da matriz");
    if n < 1 || n > MAXN {
        println!("N = {} está fora do limite permitido.", n);
        return;
    }

    // Inicializando matriz e vetor B
    unsafe {
        inicializar_matriz(n);
    }
    
    // Medindo o tempo de execução
    let inicio = Instant::now();
    unsafe {
        eliminacao_gaussiana(n);
    }
    let duracao = inicio.elapsed();

    // Exibir vetor solução X
    unsafe {
        exibir_resultado(n);
    }
    println!("Tempo de execução: {:.3?} ms", duracao.as_millis());
}

// Função para inicializar a matriz A e vetor B com valores aleatórios
unsafe fn inicializar_matriz(n: usize) {
    let mut rng = rand::thread_rng();
    for i in 0..n {
        for j in 0..n {
            A[i][j] = rng.gen::<f64>(); // Gera um número aleatório
        }
        B[i] = rng.gen::<f64>(); // Preenchendo vetor B
        X[i] = 0.0;
    }
}

// Implementação da eliminação de Gauss
unsafe fn eliminacao_gaussiana(n: usize) {
    println!("Executando eliminação de Gauss...");
    
    // Etapa de eliminação
    for norm in 0..(n - 1) {
        for row in (norm + 1)..n {
            let multiplicador = A[row][norm] / A[norm][norm];
            for col in norm..n {
                A[row][col] -= A[norm][col] * multiplicador;
            }
            B[row] -= B[norm] * multiplicador;
        }
    }
    
    // Substituição regressiva para encontrar X
    for row in (0..n).rev() {
        X[row] = B[row];
        for col in (row + 1)..n {
            X[row] -= A[row][col] * X[col];
        }
        X[row] /= A[row][row];
    }
}

// Exibir vetor solução X (caso seja pequeno o suficiente)
unsafe fn exibir_resultado(n: usize) {
    if n < 100 {
        print!("\nX = [");
        for i in 0..n {
            print!("{:.2}{}", X[i], if i < n - 1 { "; " } else { "]\n" });
        }
    }
}
