library(tidyverse)
library(xtable)

data <- read.csv2("output.csv", header = FALSE, dec = '.')
colnames(data) <- c("operation", "representation", "tnorm", "time")

data <- data |>
    mutate(time = time / 1000) |>
    pivot_wider(names_from = operation, values_from = time) |>
    rename(combine_time = Conjunct,
           supp_time = Sum) |>
    mutate(total_time = combine_time + supp_time,
           representation = gsub("Vector", "Naive", representation, fixed = TRUE))

naive <- data |>
    filter(representation == "Naive") |>
    select(-representation)

tab <- left_join(data, naive, by = "tnorm", suffix = c("", ".naive")) |>
    mutate(combine_speedup = combine_time.naive / combine_time,
           supp_speedup = supp_time.naive / supp_time,
           total_speedup = total_time.naive / total_time) |>
    mutate(combine_speedup = round(combine_speedup, 2),
           supp_speedup = round(supp_speedup, 2),
           total_speedup = round(total_speedup, 2)) |>
    select(-combine_time.naive, -supp_time.naive, -total_time.naive)

xtable(tab)
