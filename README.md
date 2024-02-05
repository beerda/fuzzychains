# fuzzychains
Testing the performance of various algorithms for fast computation of conjunction and supports of fuzzy sets


## Requirements

Run the following command to install the `cpupower` utility for disabling CPU scaling:

```
sudo apt install linux-tools-common linux-tools-generic
```


## Running the benchmark

```
# disable CPU scaling
sudo cpupower frequency-set --governor performance

<path_to_executable>/fuzzychains

# enable CPU scaling again
sudo cpupower frequency-set --governor powersave
```

