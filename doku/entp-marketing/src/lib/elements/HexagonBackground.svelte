<script lang="ts">
	import { slideIndex } from '$lib/stores';

	import Hexagon from './Hexagon.svelte';

	const rows = 13;
	const cols = 13;
</script>

<div
	class="transformer"
	user-select-none
	style={`--x:${10 * Math.sin($slideIndex * 20 + 4)}; --y:${
		10 * Math.sin($slideIndex * 20 + 8)
	}; --z:${10 * Math.sin($slideIndex * 30 + 12)}`}
>
	{#each Array(rows) as _, y}
		<div class="row" flex class:offset={y % 2 === 0}>
			{#each Array(cols) as _, x}
				<div
					class="cell"
					h-full
					style={`--alpha:${Math.sqrt((x + y) / (rows + cols))};
          --pos:${Math.random() + Math.sin(Math.sqrt((x + y) / (rows + cols)) * 4) * 5}s;`}
				>
					<div class="animator">
						<Hexagon --fill="none" --stroke="white" --stroke-width="1px" />
					</div>
				</div>
			{/each}
		</div>
	{/each}
</div>

<style>
	.transformer {
		pointer-events: none;
		right: 0vw;
		bottom: 0vw;
		filter: blur(2px);
		transform-origin: center center;
		transition: transform 3s ease;
		transform: perspective(80px)
			rotate3d(calc(var(--x) + 11), calc(var(--y) - 11), calc(var(--y) + 2), 5deg) scale(1.5);
	}

	@keyframes wobble {
		0% {
			transform: scale(1) rotate(0deg);
			opacity: 1;
		}
		20% {
			transform: scale(0.7) rotate(30deg);
			opacity: 0.8;
		}
		40% {
			transform: scale(1) rotate(60deg);
			opacity: 1;
		}
		100% {
			transform: scale(1) rotate(60deg);
		}
	}

	.animator {
		animation: wobble 30s infinite;
		animation-delay: var(--pos);
		width: 100%;
		height: 100%;
		transform-origin: 4vw 4vw;
	}

	.cell {
		width: 8vw;
		transform: scale(calc(var(--alpha) + 0.3));
		opacity: var(--alpha);
	}

	.row {
		height: 8vw;
		margin-top: -1vw;
	}

	.offset {
		transform: translateX(-4vw);
	}
</style>
